"""Pre-push gate: catch a push that would move contributor credit off its matcher.

WHY THIS EXISTS
---------------
`validate` fails a merge outright when credit moves:

    Validation failed: contributor attribution changed or was lost
    Contributor credit: 0 added, 2 changed, 0 lost

That verdict arrives from the private build box after a full merge validation -- twenty
minutes, and only once the PR is open. The failure is also invisible in review: every file
still byte-matches, every module is still exact, and the diff looks like ordinary readable
work. Nothing on your machine says otherwise. This closes that gap: same computation as the
gate, run locally in seconds.

WHAT GOES WRONG
---------------
`chaos_db_ci.first_matchers()` credits each surviving src/ path to the first contributor who
landed the match it descends from. Git's own classification decides the lineage:

    rename        -> credit carries to the new path
    delete + add  -> lineage ends; the adder becomes the new owner

#938 added a rescue for the common promotion case: a delete and an add IN ONE COMMIT whose
paths share a stem are paired as a rename, so `src/F.c -> src/F.cpp` keeps its credit. But
that stem includes the directory, so it cannot follow a file that MOVES. And `git log -M`
gives up on its own once content churn drops similarity below 50%.

So the trap is specific: **rewriting a file's contents and moving it in the same commit.**
Either alone is safe. Together, similarity falls below the threshold, the stem changes so
the pairing cannot help, and credit silently re-points to whoever pushed.

PR #993 is the worked example, and it shows how narrow the margin is. Three files moved in
one commit. The Mad Piano source survived at R056 -- barely over the threshold -- while two
message sources were rewritten a little more heavily, fell under it, and lost their lineage.
Same commit, same kind of move; the outcome turned purely on how much text changed.

THE RULE
--------
A commit may rewrite a file, or move it. Not both.

Split them: rewrite in place first, then move with an empty diff. Git records R100 and the
credit follows. That is the #869-then-#970 sequence, and it is what this check enforces.

A narrow exception is an already-unenrolled duplicate shard. Retiring that file is not a
credit move when the canonical production function keeps the same unique module, address,
size and symbol, the same matched owner, and the same explicit member credit. The shard's
historical path author stays a separate fact from that function author. A configured symbol
with no proof the deleted file was already unenrolled still fails.

Usage:
  python tools/prepush_attribution.py                          # origin/main..HEAD
  python tools/prepush_attribution.py --base origin/main
  python tools/prepush_attribution.py --json report.json

Exit status is 1 if any credit changed or was lost, so it can gate a push.
"""
import argparse
import json
import pathlib
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))

import chaos_db_ci as CDB  # noqa: E402


def attribution_at(rev):
    """Attribution policy from the revision being checked, including its aliases."""
    try:
        raw = subprocess.run(["git", "show", f"{rev}:attribution.json"], cwd=REPO,
                             capture_output=True, text=True, encoding="utf-8",
                             errors="replace", check=True).stdout
        data = json.loads(raw)
    except (subprocess.CalledProcessError, json.JSONDecodeError):
        return {}
    return data if isinstance(data, dict) else {}


def canonical_author(author, data):
    # Keep this identical to validate_merge.attribution_snapshot's resolution.
    return data.get("aliases", {}).get(str(author).lower(), author)


def credit_overrides_at(rev):
    """Canonical authors for both path and path#symbol overrides."""
    data = attribution_at(rev)
    return {key: canonical_author(author, data)
            for key, author in data.get("overrides", {}).items()
            if isinstance(key, str) and key.startswith("src/")
            and isinstance(author, str) and author}


def overrides_at(rev):
    """Path-wide attribution overrides as of ``rev``."""
    return {key: author for key, author in credit_overrides_at(rev).items()
            if "#" not in key}


def member_overrides_at(rev):
    """Unambiguous ``symbol -> (source path, author)`` consolidation overrides.

    This exact-name fallback is only for sources without configured ROM identities.
    Configured functions must follow module and address, including their new symbol
    spelling, rather than allowing a same-named function in another overlay to rescue
    missing credit.
    """
    out, ambiguous = {}, set()
    for key, author in credit_overrides_at(rev).items():
        if "#" not in key:
            continue
        path, symbol = key.rsplit("#", 1)
        if symbol:
            if symbol in out:
                ambiguous.add(symbol)
            out[symbol] = (path, author)
    return {symbol: member for symbol, member in out.items() if symbol not in ambiguous}


def source_paths_at(rev):
    """Only source files present in this revision can own contributor credit."""
    paths = subprocess.run(
        ["git", "ls-tree", "-r", "--name-only", rev, "--", "src/"],
        cwd=REPO, capture_output=True, text=True, encoding="utf-8",
        errors="replace", check=True).stdout.splitlines()
    return {path for path in paths if path.endswith((".c", ".cpp"))}


def function_ownership_at(rev):
    """Use the merge validator's revision-scoped symbol and delinks ownership."""
    import validate_merge as VM

    old_repo = VM.REPO
    VM.REPO = REPO
    try:
        # The enrolment cache is revision keyed; resolve HEAD before consulting it.
        rev = VM.resolve_commit(rev)
        matched = VM.function_snapshot(rev)["matched"]
        claims, symbols = {}, set()
        for path in VM.tree_paths(rev, "config/arm9"):
            module = VM._module_from_symbols(path)
            if module is None:
                continue
            for line in VM.git_text(rev, path).splitlines():
                row = VM.FUNC_RE.match(line)
                if not row:
                    continue
                name, size, addr = row.group(1), int(row.group(2), 16), int(row.group(3), 16)
                symbols.add(name)
                if size:
                    key = f"{module}:0x{addr:08x}"
                    claims.setdefault(key, set()).add((name, size))
        # The snapshot chooses one record per address. That is sound for a real
        # function plus zero-size aliases, but competing bodies do not establish
        # unique ownership. Never let their row order choose whose credit survives.
        ambiguous = {key for key, rows in claims.items() if len(rows) > 1}
        return matched, ambiguous, symbols, claims
    finally:
        VM.REPO = old_repo


def _configured_rows(claims):
    rows = []
    for key, pairs in claims.items():
        module, addr_text = key.split(":")
        addr = int(addr_text, 16)
        for name, size in pairs:
            rows.append((module, addr, size, name))
    return rows


def _range_covers(ranges, addr, size):
    end = addr + size
    return any(name in (".text", ".init") and lo <= addr and end <= hi
               for name, lo, hi in ranges)


def _parse_delink_entries(module, text):
    """File entries in one delinks blob, including those without ``complete``.

    Same section grammar as ``rombuild_check.ENTRY_SEC``. ``complete`` is recorded
    separately so an unenrolled duplicate can be proved without treating it as the
    production owner.
    """
    import rombuild_check as RBC

    entries, path, ranges, complete = [], None, [], False

    def flush():
        nonlocal path, ranges, complete
        if path is not None:
            entries.append({"module": module, "path": path, "complete": complete,
                            "ranges": ranges})
        path, ranges, complete = None, [], False

    for line in text.splitlines():
        if not line.strip():
            continue
        if not line[0].isspace():
            flush()
            path = line.strip().rstrip(":")
            continue
        if path is None:
            continue
        if line.strip() == "complete":
            complete = True
            continue
        row = RBC.ENTRY_SEC.match(line)
        if row:
            ranges.append((row.group(1), int(row.group(2), 16), int(row.group(3), 16)))
    flush()
    return entries


def delink_entries_at(rev):
    """Every ``src/`` delinks entry at ``rev``, complete or not."""
    import validate_merge as VM

    old_repo = VM.REPO
    VM.REPO = REPO
    try:
        rev = VM.resolve_commit(rev)
        entries = []
        for path in VM.tree_paths(rev, "config/arm9"):
            module = VM._module_from_delinks(path)
            if module is None:
                continue
            entries.extend(_parse_delink_entries(module, VM.git_text(rev, path)))
        return entries
    finally:
        VM.REPO = old_repo


def _complete_owners(entries, module, addr, size):
    found = []
    for entry in entries:
        path = entry["path"]
        if (entry["complete"] and entry["module"] == module and path.startswith("src/")
                and path not in found and _range_covers(entry["ranges"], addr, size)):
            found.append(path)
    return found


def _shard_identity(shard_path, basename, shard_entries, base_entries, base_rows):
    """The one configured function this deleted file duplicates, or None.

    Proof it was already unenrolled is positive. A ``complete`` entry is enrolled
    production, not a duplicate. A non-complete entry must name this path and cover
    exactly one configured function. A path no delinks entry names is unenrolled
    only when its basename is that unique symbol and a different path is the sole
    complete owner. Either proof has to be read off the base revision.
    """
    if any(entry["complete"] for entry in shard_entries):
        return None
    if shard_entries:
        if len({entry["module"] for entry in shard_entries}) != 1:
            return None
        covered = []
        for entry in shard_entries:
            for row in base_rows:
                if (entry["module"] == row[0] and row not in covered
                        and _range_covers(entry["ranges"], row[1], row[2])):
                    covered.append(row)
        if len(covered) != 1:
            return None
        identity = covered[0]
        # A configured basename is that symbol's shard, not some other function
        # whose range happens to contain the entry.
        if any(row[3] == basename for row in base_rows) and basename != identity[3]:
            return None
        return identity
    named = [row for row in base_rows if row[3] == basename]
    if len(named) != 1:
        return None
    module, addr, size, _name = named[0]
    owners = _complete_owners(base_entries, module, addr, size)
    if len(owners) != 1 or owners[0] == shard_path:
        return None
    return named[0]


def _one(rows, pred):
    matched = [row for row in rows if pred(row)]
    return matched[0] if len(matched) == 1 else None


def classify_shard_retirement(old_stem, path_author, base_paths, base_matched,
                              head_matched, base_claims, head_claims, ambiguous,
                              base_entries, head_entries, base_overrides,
                              head_overrides):
    """Retirement of one already-unenrolled duplicate, or None if this is not one.

    A hit is ``("retired"|"changed"|"lost", row)``. Retired rows keep the shard's
    historical path author apart from the canonical function author; those two
    people are not required to match, and a difference is not a credit change.
    ``changed`` compares the explicit member credit only. Missing proof returns
    None so a configured symbol still fails through the ordinary path.
    """
    shard_paths = [path for path in base_paths if path.rsplit(".", 1)[0] == old_stem]
    if len(shard_paths) != 1:
        return None
    shard_path = shard_paths[0]
    basename = old_stem.rsplit("/", 1)[-1]
    base_rows = _configured_rows(base_claims)
    head_rows = _configured_rows(head_claims)
    shard_entries = [entry for entry in base_entries if entry["path"] == shard_path]
    identity = _shard_identity(shard_path, basename, shard_entries, base_entries, base_rows)
    if identity is None:
        return None
    module, addr, size, symbol = identity
    key = f"{module}:0x{addr:08x}"
    lost = ("lost", (basename, old_stem, path_author))
    if _one(head_rows, lambda row: row == identity) is None:
        return lost
    if _one(base_rows, lambda row: row[3] == symbol) is None:
        return lost
    if _one(head_rows, lambda row: row[3] == symbol) is None:
        return lost
    if _one(base_rows, lambda row: row[0] == module and row[1] == addr) is None:
        return lost
    if _one(head_rows, lambda row: row[0] == module and row[1] == addr) is None:
        return lost
    if key in ambiguous:
        return lost
    base_rec, head_rec = base_matched.get(key), head_matched.get(key)
    if (not base_rec or not head_rec or base_rec["srcPath"] != head_rec["srcPath"]
            or base_rec["srcPath"] == shard_path or base_rec["name"] != symbol
            or head_rec["name"] != symbol or base_rec["size"] != size
            or head_rec["size"] != size):
        return lost
    owner = base_rec["srcPath"]
    if _complete_owners(base_entries, module, addr, size) != [owner]:
        return lost
    if _complete_owners(head_entries, module, addr, size) != [owner]:
        return lost
    member = f"{owner}#{symbol}"
    old_fn, new_fn = base_overrides.get(member), head_overrides.get(member)
    if not old_fn or not new_fn:
        return lost
    if old_fn != new_fn:
        return ("changed", (symbol, old_stem, owner, old_fn, new_fn))
    return ("retired", (symbol, old_stem, owner, path_author, old_fn))


def lineage(rev):
    """{stem-without-extension: handle} at `rev`, resolved the way the merge gate resolves it.

    This must be the COMPOSITE -- overrides, then finishers, then first_matchers -- because
    that is exactly what `validate_merge.attribution_snapshot` compares, and a gate that
    models only part of it reports clean on pushes the gate rejects.

    Checking `first_matchers` alone left a gap wide enough to lose real credit through. A
    1,798-file relocation passed this check with "0 changed, 0 lost" while quietly moving 75
    functions' composite author to whoever ran the move: `match_finishers` carried a file's
    draft history across the rename but not its finisher, so every moved file read as a fresh
    finish by the mover. The finisher layer is fixed in chaos_db_ci now; this makes the gate
    able to see that layer at all, so the next such bug fails here instead of at merge.

    Keyed on the path minus its extension rather than the full path, because a legitimate
    move or a .c -> .cpp promotion changes the path while the function -- and therefore who
    deserves credit for it -- stays the same. Comparing full paths would report every
    intentional move as a loss.
    """
    first = CDB.first_matchers(rev)
    finishers = CDB.match_finishers(rev)
    overrides = overrides_at(rev)
    data = attribution_at(rev)
    out = {}
    paths = source_paths_at(rev)
    for path in (set(first) | set(finishers) | set(overrides)) & paths:
        who = overrides.get(path) or canonical_author(finishers.get(path) or first.get(path), data)
        if who:
            out[path.rsplit(".", 1)[0]] = who
    return out


def basename_key(stem):
    return stem.rsplit("/", 1)[-1]


def renames_between(base, head):
    """{old basename: new basename} for renames git itself detected under src/.

    Why this exists: `lineage` keys on the basename so that a directory move or a
    `.c -> .cpp` promotion is not read as a loss. A **symbol correction** changes
    the basename itself -- `_ZN5SceneD2Ev` is really `BootScene`'s D1, so the file
    has to be called something else -- and without this the old name simply
    vanishes and reads as lost, no matter how the commits are arranged.

    That was not hypothetical. Splitting rewrite from move exactly as THE RULE
    above prescribes still reported 8 lost, because that remedy addresses
    *similarity*-based lineage loss and this is *identity* loss. #1160 hit the same
    wall (`_ZN3IRQ13DmaTimHandlerEv` -> `...Ej`) and landed with the loss recorded.

    The gate keeps its teeth: this consults git's own rename detection -- the same
    authority `first_matchers` relies on via `git log -M` -- so a delete+add git
    does NOT pair stays unpaired here, and a pairing whose credit actually moved is
    reported as changed rather than waved through. Verified by rewriting and moving
    a file in one commit: still 1 lost, still exit 1.

    Renames are collected **per commit and returned in order**, not from one
    base..head diff, and are replayed rather than composed -- see project(). That matters for exactly the sequence THE RULE prescribes: rewrite in one
    commit, move in the next. Across the whole range those two show up as a single
    change whose similarity can fall under git's 50% threshold -- which it did for 3
    of 8 real cases, the small files whose comments were rewritten most. Per commit,
    the move is the R100 git already recorded.
    """
    log = subprocess.run(
        ["git", "log", "-M", "--reverse", "--name-status", "--format=@@%H",
         f"{base}..{head}", "--", "src/"],
        cwd=REPO, capture_output=True, text=True, encoding="utf-8", errors="replace")

    steps = []
    for ln in log.stdout.splitlines():
        parts = ln.split("\t")
        if len(parts) == 3 and parts[0].startswith("R"):
            old = basename_key(parts[1].rsplit(".", 1)[0])
            new = basename_key(parts[2].rsplit(".", 1)[0])
            if old != new:
                steps.append((old, new))

    return steps


def project(before_by_name, steps):
    """Replay `steps` in COMMIT ORDER onto a moving {name: credit} map.

    This used to compose the steps into a single {old: final} map and chase it
    forward, which is right for a file that really moved A -> B -> C over time and
    WRONG for a permutation. Renaming a family of classes so each takes the next
    one's name produces, in this order:

        commit 1   VirtualDoor -> Exit
        commit 3   CameraTag   -> VirtualDoor

    Chased forward, those compose to `CameraTag -> Exit`: the map says CameraTag's
    credit ended up on Exit, when Exit's credit is VirtualDoor's and CameraTag's is
    on VirtualDoor. Every name in the cycle then reads as CREDIT CHANGED even though
    git recorded an R100 for each step and no author lost anything. Order is the
    whole point -- step 2 only means what it means because step 1 already vacated
    the name.

    Replaying is also strictly stricter than composing, not looser: a rewrite-and-
    move in one commit is still not a rename to git, so it contributes no step, the
    old name is still projected as present, and it is still reported lost.
    """
    state = dict(before_by_name)
    origin = {name: name for name in state}
    for old, new in steps:
        if old not in state:
            continue
        state[new] = state.pop(old)
        origin[new] = origin.pop(old, old)
    return state, origin


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--base", default="origin/main", help="revision to compare against")
    ap.add_argument("--head", default="HEAD")
    ap.add_argument("--json", help="write a JSON report here")
    args = ap.parse_args()

    try:
        subprocess.run(["git", "rev-parse", "--verify", args.base], cwd=REPO, check=True,
                       capture_output=True)
    except subprocess.CalledProcessError:
        sys.exit(f"cannot resolve {args.base} -- fetch first?")

    before, after = lineage(args.base), lineage(args.head)

    # Directory moves change the stem but not the filename, so compare on the filename to
    # tell "this file moved" apart from "this file's credit moved".
    before_by_name = {basename_key(s): (s, w) for s, w in before.items()}
    after_by_name = {basename_key(s): (s, w) for s, w in after.items()}

    steps = renames_between(args.base, args.head)
    # Where each name's credit SHOULD have ended up, following git's own rename
    # detection step by step. Comparing `after` against this instead of against
    # `before` is what lets a deliberate symbol correction pass while a
    # rewrite-and-move in one commit still fails.
    projected, origin = project(before_by_name, steps)

    missing = {name: old for name, old in projected.items() if name not in after_by_name}
    moved = any(old_stem != after_by_name[name][0]
                for name, (old_stem, _who) in projected.items() if name in after_by_name)
    if missing or moved:
        base_functions, base_ambiguous, base_symbols, base_claims = function_ownership_at(args.base)
        head_functions, head_ambiguous, _head_symbols, head_claims = function_ownership_at(args.head)
        ambiguous = base_ambiguous | head_ambiguous
        by_stem, head_by_stem = {}, {}
        for key, rec in base_functions.items():
            by_stem.setdefault(rec["srcPath"].rsplit(".", 1)[0], []).append((key, rec))
        for key, rec in head_functions.items():
            head_by_stem.setdefault(rec["srcPath"].rsplit(".", 1)[0], []).append((key, rec))

        # A promotion may keep the factory's filename, including its directory.
        # That survivor now owns several functions: its file author cannot stand
        # in for each member's explicit credit. Send it through the same strict
        # address/size/override checks as the sources the TU absorbed. Ordinary
        # single-function moves retain the file-lineage check below, and changes
        # with no moved or missing paths avoid the full ownership scans.
        for name, (old_stem, old_who) in projected.items():
            if name not in after_by_name:
                continue
            new_stem = after_by_name[name][0]
            owned = by_stem.get(old_stem, [])
            dests = head_by_stem.get(new_stem, [])
            if len(dests) > 1 and (old_stem != new_stem
                                  or {key for key, _rec in owned}
                                  != {key for key, _rec in dests}):
                missing[name] = (old_stem, old_who)

    changed, lost, moved_ok, renamed_ok, consolidated_ok, retired_ok = [], [], [], [], [], []
    for name, (new_stem, new_who) in after_by_name.items():
        if name not in projected or name in missing:
            continue                                   # new work or function-level check
        old_stem, old_who = projected[name]
        came_from = origin.get(name, name)
        if old_who != new_who:
            changed.append((name, old_stem, new_stem, old_who, new_who))
        elif came_from != name:
            renamed_ok.append((came_from, name, old_stem, new_stem, old_who))
        elif old_stem != new_stem:
            moved_ok.append((name, old_stem, new_stem, old_who))
    if missing:
        base_overrides = credit_overrides_at(args.base)
        head_overrides = credit_overrides_at(args.head)
        members = member_overrides_at(args.head)
        head_paths = source_paths_at(args.head)
        base_paths = source_paths_at(args.base)
        base_entries = delink_entries_at(args.base)
        head_entries = delink_entries_at(args.head)
        for name, (old_stem, old_who) in missing.items():
            owned = by_stem.get(old_stem)
            if owned:
                # A file can own several differently credited functions. Check every
                # identity and require a current, explicit per-member override.
                for key, rec in owned:
                    old_author = base_overrides.get(f"{rec['srcPath']}#{rec['name']}") or old_who
                    dest = head_functions.get(key)
                    new_author = (head_overrides.get(f"{dest['srcPath']}#{dest['name']}")
                                  if dest and dest["size"] == rec["size"]
                                  and key not in ambiguous else None)
                    if not new_author:
                        lost.append((rec["name"], old_stem, old_author))
                    elif new_author != old_author:
                        changed.append((rec["name"], old_stem, dest["srcPath"],
                                        old_author, new_author))
                    else:
                        consolidated_ok.append((rec["name"], old_stem, dest["srcPath"],
                                                old_author))
                continue

            # Not the matched owner. A duplicate shard can still carry its own path
            # author. Retire it only with proof it was already unenrolled; the path
            # author is not the canonical function author and must not be collapsed
            # into that credit. Anything short of that proof keeps failing below.
            verdict = classify_shard_retirement(
                old_stem, old_who, base_paths, base_functions, head_functions,
                base_claims, head_claims, ambiguous, base_entries, head_entries,
                base_overrides, head_overrides)
            if verdict is not None:
                kind, row = verdict
                {"retired": retired_ok, "changed": changed, "lost": lost}[kind].append(row)
                continue

            # An unresolved configured symbol has no ownership proof. Only genuinely
            # unconfigured sources can use the legacy exact-symbol fallback.
            member = (members.get(name)
                      if basename_key(old_stem) not in base_symbols else None)
            if member and member[0] not in head_paths:
                member = None
            if member and member[1] == old_who:
                consolidated_ok.append((name, old_stem, member[0], old_who))
            elif member:
                changed.append((name, old_stem, member[0], old_who, member[1]))
            else:
                lost.append((origin.get(name, name), old_stem, old_who))

    for name, old_stem, new_stem, old_who, new_who in changed:
        print(f"  CREDIT CHANGED  {name}")
        print(f"      {old_stem}  [{old_who}]")
        print(f"   -> {new_stem}  [{new_who}]")
    for name, old_stem, old_who in lost:
        print(f"  CREDIT LOST     {name}  was {old_stem} [{old_who}]")
    for name, old_stem, new_stem, who in moved_ok:
        print(f"  moved, credit intact: {name}  [{who}]")
    for name, target, old_stem, new_stem, who in renamed_ok:
        print(f"  renamed, credit intact: {name} -> {target}  [{who}]")
    for name, old_stem, new_path, who in consolidated_ok:
        print(f"  consolidated, credit intact: {name}  {old_stem} -> {new_path}  [{who}]")
    for symbol, old_stem, owner, path_author, function_author in retired_ok:
        print(f"  retired duplicate, credit intact: {symbol}  {old_stem} [{path_author}]"
              f"  canonical {owner} [{function_author}]")

    print(f"\n{len(after_by_name)} tracked, {len(moved_ok)} moved with credit intact, "
          f"{len(renamed_ok)} renamed with credit intact, "
          f"{len(consolidated_ok)} consolidated with credit intact, "
          f"{len(retired_ok)} retired with credit intact, "
          f"{len(changed)} changed, {len(lost)} lost")

    if args.json:
        pathlib.Path(args.json).write_text(json.dumps(
            {"changed": changed, "lost": lost, "moved_ok": moved_ok,
             "renamed_ok": renamed_ok, "consolidated_ok": consolidated_ok,
             "retired_ok": retired_ok}, indent=2),
            encoding="utf-8")

    if changed or lost:
        print("\nA commit may rewrite a file, or move it -- not both. Split them: rewrite in")
        print("place, then move with an empty diff, so git records R100 and credit follows.")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
