#!/usr/bin/env python3
"""Run the static gates on the MERGE RESULT, before the merge, and diff the verdicts.

WHAT IT GATES
-------------
Not a branch. Not main. The tree `git merge` would produce if this PR landed right
now -- `git merge-tree --write-tree origin/main <head>` -- which is a tree that has
never existed on disk and that nothing in this repository has ever run a gate over.
Every gate is run twice, once on that tree and once on an export of `origin/main`
itself, and the two verdicts are printed side by side. The only thing this tool
fails on is a gate that is GREEN on the base and RED on the merge result.

WHY EVERY OTHER GATE IS BLIND TO THIS
-------------------------------------
`.github/workflows/pr-validate.yml` -- the job that submits to the external ROM
validator, and the only job in this tree that builds anything -- has exactly one
trigger:

    on:
      pull_request_target:

There is no `push: branches: [main]`. So **no ROM is built after a merge, ever**,
and every PR is judged against ITS OWN BASE. Two PRs that are each honestly green
can combine into a red main and nothing observes it until a person notices. That
has happened twice in four days here (#1987, #1990, both `tools/`-only changes that
landed against a base that had moved).

`.github/workflows/source-coverage.yml` is the one job that partly closes the hole:
it also runs on push to main against `github.event.before`, main's previous tip. But
that fires AFTER the merge. It tells you main is broken; it cannot tell you not to
break it. And it is one metric out of the seven gates below.

The gap this fills is therefore narrow and specific: the static gates, on the merge
result, BEFORE the merge.

WHAT THIS IS NOT: tools/validate_merge.py
------------------------------------------
`validate_merge.py` also reasons about a merge, and the overlap is worth stating so
this is not read as a second copy of it. That tool builds the report the EXTERNAL
validator publishes: the private worker owns the ROM and the compiler, commits a test
merge, runs `rombuild.py` on both sides and hands the JSON to `validate_merge.py` to
turn into a verdict. It is the authority on bytes, it is the only thing that can be,
and none of it runs here -- it needs the ROM, the compiler, and a worker this repo
does not control. It also runs on `pull_request_target`, which means it too is
answering the question against the PR's own base.

This tool runs on a laptop, in a second, over a tree that has no commit, and answers
only what text can answer. The two do not overlap; they do not even share a question.

THIS IS NOT HYPOTHETICAL
------------------------
Run by hand on 2026-08-29 against PR #2001: green on its own PR, clean-merging, no
conflict. The merge result turned `converted-ratchet` RED, because
`src/actors/ActorDerived.cpp` had landed in one of the sixteen commits the PR was
behind. Neither side shows this. The PR's tree is green. Main is green. Only the
tree that does not yet exist is red.

WHY IT NEVER BLAMES A PR FOR A RED BASE
---------------------------------------
The exit code is driven by the DIFF of two verdicts, never by the merge result's
verdict alone. A gate that is already red on `origin/main` stays red on every merge
result computed from it, and reporting that as this PR's failure would be wrong four
times over: it is not the PR's bug, the PR cannot fix it, the author would have to
learn to ignore the tool to get anything landed, and a tool people ignore gates
nothing. So a red base is printed, prominently, as `pre-existing` -- and contributes
zero to the exit code.

The four outcomes, and what each one means:

    base    merge   verdict         what to do
    ----    -----   -------         ----------
    pass    pass    ok              nothing
    pass    FAIL    REGRESSION      this is the PR's, and only this fails the run
    FAIL    FAIL    pre-existing    main is broken; not this PR's to own
    FAIL    pass    fixed           the PR repairs a broken base; still exit 0

WHY IT COMPILES NOTHING, AND WHY THAT IS A HARD REQUIREMENT
-----------------------------------------------------------
It never invokes `tools/rombuild.py` or `tools/eligible.py`, and it must not be
extended to. `build/` is shared between worktrees in this repo's normal working
setup, so two concurrent ROM builds clobber each other's intermediate state and
produce failures that belong to neither. A gate that needed a ROM build could not
run alongside the work it gates -- the same reasoning `source-coverage.yml` records
for staying on a GitHub runner. Everything below is `git cat-file` plus text
parsing.

The cost of that is stated honestly rather than hidden: this tool cannot see a byte
regression. A merge result that breaks the ROM link, or that makes a function stop
reproducing, is invisible here and always will be. What it sees is the seven static
gates, which is seven more than run today.

THE GATES, AND WHICH ONES WERE VERIFIED TOOLCHAIN-FREE
------------------------------------------------------
Each was read before inclusion, because several tools in this tree self-`return`
when the compiler or `extracted/` is missing and report a PASS rather than a skip --
a fast green that means nothing. Included:

  converted-ratchet   tools/tiers_ratchet.py --check
                      Pure. `tiers.py` imports `delaunder` for `code_mask` only and
                      `demangle` for string work; neither reads a ROM. Needs
                      `git ls-files src` -- see THE `git init` STEP. Refuses an
                      absent baseline with exit 2 rather than treating it as an
                      empty set, so it cannot pass vacuously. ~70s, the slow one.

  source-coverage     tools/source_coverage.py --json
                      A DELTA gate, handled specially: see BYTES, BELOW.

  dead-references     tools/check_dead_references.py
                      Pure text over prose files. Carries its own anti-hollow guard
                      (`SCAN TOO SMALL`, exit 2) so a scan that found nothing cannot
                      report clean. Needs `git ls-files -z`.

  src-tu-refs         tools/check_src_tu.py
                      Resolves mangled references in `src_tu/` against
                      `config/**/symbols.txt`. Text only -- the compiling half of
                      this check lives in `check_src_tu_compiles.py`, which is
                      EXCLUDED below for exactly that reason.

  header-offsets      tools/check_header_offsets.py <every tracked header>
                      Pure text. Refuses an empty file list ("an empty check is not
                      a pass"), which this tool relies on: if `git ls-files` yields
                      no headers the gate is recorded as an ERROR, not a pass.
                      Invoked in batches to stay under the Windows argv limit.

  layout-check        tools/layout_check.py
                      Filesystem and `config/**/delinks.txt` only.

  duplicate-sources   tools/check_duplicate_sources.py
                      Filesystem only. Worth its second in this particular tool: a
                      doubled stem is a *merge-shaped* defect. One PR renames
                      `X.c` -> `X.cpp`, another edits `X.c`; git merges both
                      happily and the result has both halves, one of which is
                      compiled by nothing and checked by nothing.

Deliberately EXCLUDED, each for a stated reason -- none of these is toolchain-free,
and including one would buy a green that means nothing:

  check_references.py         reads build/rombuild-eligibility.json, which only
                              `eligible.py` produces, and then validates its commit
                              stamp against HEAD. An exported tree has no HEAD.
  check_data_definitions.py   reads the objects `eligible.py` leaves in build/src/.
  check_layout_free.py        reads `extracted/` (the ROM dump) and needs PyYAML.
  check_python_names.py       needs pyflakes, which is not stdlib.
  check_src_tu_compiles.py    needs mwccarm.
  rombuild.py, eligible.py    forbidden outright, see above.

BYTES, BELOW: WHY source_coverage IS NOT RUN WITH `--check`
-----------------------------------------------------------
`source_coverage.py --check` wants a git ref to compare against, and the merge
result is a bare tree with no commit -- there is no ref to hand it. So it is run in
its no-base reporting mode (`--json`) on BOTH trees and the numbers are subtracted
here. This is the one gate whose base verdict is `pass` by construction -- it is the
reference the merge result is measured against, so it has no independent verdict of
its own, and the table says `(ref)` rather than `pass` to keep that visible.

THE UNIT IS THE BYTE, AND ONLY THE BYTE. `currentBytes` and the per-section map
decide the verdict; `entries` and `modules` are printed as context and can never
fail a run. That distinction is not fastidiousness, it is a measurement. The first
version of this tool failed on a decrease in ANY of the four numbers, and the first
time it was pointed at real PRs it called two of them red -- #2023 (`entries` 11025
-> 11011) and #2024 (11025 -> 11017) -- with `currentBytes` and every per-section
total UNCHANGED. Both are TU promotions, and that is exactly the false alarm
`source_coverage.py` exists to avoid: promotion re-partitions the address space, so
thirty-eight per-function delinks entries become three merged ones covering the same
bytes and the entry count falls by construction with nothing handed back to the
cartridge. A gate that goes red on every TU promotion is a gate people learn to
click past, which is the same failure as a gate that never goes red at all.

THE `git init` STEP, WHICH IS NOT OPTIONAL
------------------------------------------
A tree exported with `git checkout-index --prefix=` is a plain directory, and four
of the gates above shell out to `git -C <repo> ls-files`, which fails there with
exit 128 -- reported by the gate as an error, or in the worst shape as an empty file
list. So each export gets a `git init` and a copy of the temporary index the export
was made from. That index is the whole point: it is what makes `ls-files` enumerate
the merge result's files rather than nothing.

WHAT A LEGITIMATE FAILURE LOOKS LIKE
-------------------------------------
`REGRESSION` on a gate means: rebase the PR onto current main (or merge main into
it) and fix what the combination broke, exactly as if CI had failed -- because the
combination genuinely is broken, and merging it makes main red for everybody. The
usual cause is a baseline or a ratchet: the PR was cut when the banked set was
smaller, and a file that landed meanwhile no longer passes.

`CONFLICT` is reported separately and is not a gate failure. It means `git
merge-tree` could not produce a tree at all, so there was nothing to run gates on;
the PR needs a rebase before this question can even be asked.

ADVISORY, ON PURPOSE
--------------------
Nothing in `.github/workflows/` runs this. It is a command you run before you press
merge, or before you tell somebody else to. Wiring it into CI is a separate decision
with its own costs -- ~90 seconds per PR, a second full checkout, and a gate that
goes red for reasons the PR author did not write -- and that decision is not made
here.

USAGE
-----
    python tools/premerge_check.py 2001                 # a PR number
    python tools/premerge_check.py 2001 2003 2011       # several; one base export
    python tools/premerge_check.py <head-sha>           # any commit-ish
    python tools/premerge_check.py origin/main          # must be all-green, exit 0
    python tools/premerge_check.py 2001 --fetch         # pull the head object first
    python tools/premerge_check.py 2001 --json
    python tools/premerge_check.py 2001 --keep-trees    # leave the exports on disk

`gh` knows a PR's head sha; this clone may not have the OBJECT. Without `--fetch`
that is a named error with the `git fetch origin pull/N/head` to fix it, not a
`merge-tree` failure about "something we can merge". The default is not to touch the
network -- or the object store -- unless asked.

The base export and its gate run happen ONCE and are reused by every target, so six
PRs in one invocation cost roughly one base run plus six merge runs, not twelve runs.

Exit codes:
    0   no gate went green -> red
    1   at least one REGRESSION
    2   the tool could not answer (bad ref, gh missing, git too old, export failed)
    3   at least one target CONFLICTS and nothing regressed

Stdlib only. Exported trees are removed with `shutil.rmtree`; git's own removal is
never used, because in this repo a worktree's `extracted/` is an NTFS junction to
the only surviving ROM dump and git's remover recurses through it.
"""
import argparse
import json
import os
import pathlib
import re
import shutil
import subprocess
import sys
import tempfile

REPO = pathlib.Path(__file__).resolve().parent.parent

# Per-gate wall clock. converted-ratchet is ~70s on this tree; the rest are seconds.
GATE_TIMEOUT = 900

# `git ls-files` can hand back 500+ headers and Windows caps a command line at 32k.
HEADER_BATCH = 120


# --------------------------------------------------------------------------- #
# Gate definitions.
#
# `commands(tree)` returns a LIST of argv lists so a gate can be batched; the gate's
# return code is the worst of them. Everything here must be pure Python over the
# exported tree -- see the module docstring for what was excluded and why.
# --------------------------------------------------------------------------- #

def _headers(tree):
    """Every tracked header, via the index the export carries.

    Returns [] when git cannot answer, which the caller turns into an ERROR rather
    than a pass -- check_header_offsets exits 1 on an empty list by design, and
    reading that as a gate failure would blame the PR for a broken export.
    """
    out = subprocess.run(["git", "-C", str(tree), "ls-files",
                          "include/*.h", "include/**/*.h"],
                         capture_output=True, text=True)
    if out.returncode != 0:
        return []
    return [ln for ln in out.stdout.splitlines() if ln.strip()]


def _header_commands(tree):
    hdrs = _headers(tree)
    if not hdrs:
        return None  # -> ERROR: an empty header check is not a pass
    return [[sys.executable, "tools/check_header_offsets.py", *hdrs[i:i + HEADER_BATCH]]
            for i in range(0, len(hdrs), HEADER_BATCH)]


GATES = [
    {
        "key": "converted-ratchet",
        "commands": lambda t: [[sys.executable, "tools/tiers_ratchet.py", "--check"]],
        "note": "pure python; needs git ls-files; refuses an absent baseline",
    },
    {
        "key": "dead-references",
        "commands": lambda t: [[sys.executable, "tools/check_dead_references.py"]],
        "note": "pure text; own SCAN TOO SMALL guard",
    },
    {
        "key": "src-tu-refs",
        "commands": lambda t: [[sys.executable, "tools/check_src_tu.py"]],
        "note": "text only; the compiling half is check_src_tu_compiles.py (excluded)",
    },
    {
        "key": "header-offsets",
        "commands": _header_commands,
        "note": "pure text; batched; empty file list is an ERROR, not a pass",
    },
    {
        "key": "layout-check",
        "commands": lambda t: [[sys.executable, "tools/layout_check.py", "--quiet"]],
        "note": "filesystem + config/**/delinks.txt",
    },
    {
        "key": "duplicate-sources",
        "commands": lambda t: [[sys.executable, "tools/check_duplicate_sources.py"]],
        "note": "filesystem only; a merge-shaped defect",
    },
]

# Handled outside GATES: it has no verdict of its own, only a delta. See BYTES, BELOW.
COVERAGE_GATE = "source-coverage"

# THE UNIT IS THE BYTE, AND ONLY THE BYTE. `entries` and `modules` are reported as
# context and can never fail a run -- see coverage_context() for the measurement that
# proved this, on real PRs, the first time this tool was pointed at them.
COVERAGE_BYTE_KEYS = ("currentBytes",)
COVERAGE_CONTEXT_KEYS = ("entries", "modules")


# --------------------------------------------------------------------------- #
# Pure logic. Everything below this line is a function of data, not of the
# filesystem, so tools/test_premerge_check.py can exercise it with no git, no gh,
# no compiler and no extracted/.
# --------------------------------------------------------------------------- #

def classify(base_status, merge_status):
    """One gate's verdict pair -> the word that goes in the table.

    `pass` and anything-else. An ERROR is red: a gate that could not run on the merge
    result but ran on the base is a real signal about the merge result, and calling
    it a pass is how gates come to mean nothing.
    """
    base_ok = base_status == "pass"
    merge_ok = merge_status == "pass"
    if base_ok and merge_ok:
        return "ok"
    if base_ok and not merge_ok:
        return "REGRESSION"
    if not base_ok and merge_ok:
        return "fixed"
    return "pre-existing"


def diff_verdicts(base, merge):
    """[{gate, base, merge, verdict}] for every gate either side reports.

    `base` and `merge` are {gate_key: {"status": ...}}. A gate missing from one side
    is recorded as `absent`, which is not a pass, so a gate that vanished from the
    merge result surfaces as a REGRESSION rather than silently dropping out of the
    table.
    """
    rows = []
    for key in sorted(set(base) | set(merge)):
        b = base.get(key, {}).get("status", "absent")
        m = merge.get(key, {}).get("status", "absent")
        rows.append({"gate": key, "base": b, "merge": m,
                     "verdict": classify(b, m)})
    return rows


def regressions(rows):
    return [r for r in rows if r["verdict"] == "REGRESSION"]


def coverage_regressions(base_metrics, merge_metrics):
    """Every BYTE counter that went DOWN from base to merge result, as prose lines.

    `currentBytes` and every key of the per-section map -- and deliberately NOT
    `entries` or `modules`; see coverage_context().

    Increases and new sections are silent: adding coverage is the point. A section
    that DISAPPEARS is a decrease to zero and is reported as one -- that is exactly
    the shape of a delinks entry deleted outright, which `layout_check` reports as
    INFO and can never fail on.
    """
    if base_metrics is None or merge_metrics is None:
        return []
    out = []
    for key in COVERAGE_BYTE_KEYS:
        b, m = base_metrics.get(key), merge_metrics.get(key)
        if isinstance(b, int) and isinstance(m, int) and m < b:
            out.append(f"{key}: {b} -> {m} ({m - b})")
    b_sec = base_metrics.get("bySection") or {}
    m_sec = merge_metrics.get("bySection") or {}
    for sec in sorted(b_sec):
        b = b_sec.get(sec, 0)
        m = m_sec.get(sec, 0)
        if m < b:
            out.append(f"bySection[{sec}]: {b} -> {m} ({m - b})")
    return out


def coverage_context(base_metrics, merge_metrics, byte_regressions=()):
    """`entries` and `modules` movement. Printed, never fatal, and here is why.

    The first version of this tool failed a run on any decrease in any of the four
    numbers `source_coverage.py --json` reports. Pointed at real PRs on 2026-08-30 it
    immediately called two of them red -- #2023 (`entries` 11025 -> 11011) and #2024
    (11025 -> 11017) -- with `currentBytes` and every per-section total UNCHANGED.

    Both are TU-promotion PRs, and that is precisely the false alarm
    `source_coverage.py` was written to avoid; its own docstring spells it out. TU
    promotion re-partitions the address space: thirty-eight per-function delinks
    entries become three merged ones covering the same bytes. The entry count drops
    by construction and NOTHING has been handed back to the cartridge. Comparing
    entry counts reports every consolidation as a loss.

    So the unit is the covered byte set, exactly as it is in the tool being wrapped.
    `entries` and `modules` are still shown, because a large swing in either is worth
    a glance, but they cannot fail a run. A gate that reddens on every TU promotion
    is a gate people learn to click past.
    """
    if base_metrics is None or merge_metrics is None:
        return []
    out = []
    for key in COVERAGE_CONTEXT_KEYS:
        b, m = base_metrics.get(key), merge_metrics.get(key)
        if isinstance(b, int) and isinstance(m, int) and m != b:
            # The reassuring reading is only available when the bytes really are
            # flat. If bytes ALSO fell, the drop is corroborating a real loss and
            # must not be labelled a consolidation.
            note = ("  (consolidation, not a loss -- bytes are flat)"
                    if m < b and not byte_regressions else "")
            out.append(f"{key}: {b} -> {m} ({m - b:+d}){note}")
    return out


def parse_merge_tree(rc, stdout):
    """`git merge-tree --write-tree` output -> (tree_sha, conflicts).

    Exit 0 is a clean merge and stdout's first line is the tree. Exit 1 means git
    still wrote a tree but recorded conflicts; the first line is that tree and the
    rest describes them. Anything else is git refusing to answer -- no tree, and the
    caller must report a TOOL ERROR, not a conflict and not a gate failure.
    """
    lines = stdout.splitlines()
    first = lines[0].strip() if lines else ""
    is_oid = bool(re.fullmatch(r"[0-9a-f]{40,64}", first))
    if rc == 0:
        if not is_oid:
            return None, ["git merge-tree exited 0 but wrote no tree oid"]
        return first, []
    if rc == 1:
        detail = [ln for ln in lines[1:] if ln.strip()]
        return (first if is_oid else None), detail or ["conflict (no detail reported)"]
    return None, None  # None conflicts == "git could not answer at all"


def is_pr_number(spec):
    return bool(re.fullmatch(r"#?\d+", spec.strip()))


def resolve_pr(spec, runner=subprocess.run):
    """PR number -> (head_sha, label). Raises ValueError with a sentence, never a traceback.

    `runner` is injected so the failure paths -- gh absent, gh unauthenticated, PR
    not found -- are testable with no gh installed. That matters more than usual
    here: an unauthenticated gh is the single most likely way a person meets this
    tool for the first time, and a traceback would read as the tool being broken.
    """
    num = spec.strip().lstrip("#")
    argv = ["gh", "pr", "view", num, "--json", "headRefOid,title,state,baseRefName"]
    try:
        out = runner(argv, capture_output=True, text=True)
    except FileNotFoundError:
        raise ValueError(
            f"cannot resolve PR #{num}: the `gh` CLI is not on PATH.\n"
            f"  Install it, or pass the head sha directly: "
            f"premerge_check.py <sha>")
    except OSError as exc:
        raise ValueError(f"cannot resolve PR #{num}: could not run gh ({exc})")
    if out.returncode != 0:
        err = (out.stderr or "").strip().splitlines()
        hint = err[-1] if err else f"gh exited {out.returncode}"
        raise ValueError(
            f"cannot resolve PR #{num}: {hint}\n"
            f"  If this is an auth problem, `gh auth login`. If the PR is in another\n"
            f"  repository, pass the head sha directly instead of a number.")
    try:
        data = json.loads(out.stdout)
    except (ValueError, TypeError):
        raise ValueError(f"cannot resolve PR #{num}: gh returned no usable JSON")
    sha = data.get("headRefOid")
    if not sha:
        raise ValueError(f"cannot resolve PR #{num}: gh reported no headRefOid")
    title = (data.get("title") or "").strip()
    label = f"#{num} {title}"[:72] if title else f"#{num}"
    return sha, label


# --------------------------------------------------------------------------- #
# git plumbing.
# --------------------------------------------------------------------------- #

def git(repo, *args, check=False):
    out = subprocess.run(["git", "-C", str(repo), *args],
                         capture_output=True, text=True)
    if check and out.returncode != 0:
        raise RuntimeError(f"git {' '.join(args)}: {out.stderr.strip()}")
    return out


def git_supports_write_tree(repo):
    out = git(repo, "merge-tree", "-h")
    return "--write-tree" in (out.stdout + out.stderr)


def export_tree(repo, tree_sha, dest, scratch):
    """Materialise a tree at `dest`, with a working `git ls-files`.

    Three steps, and the third is the one people rediscover the hard way. A tree
    checked out with `checkout-index --prefix=` is a plain directory: `git -C dest
    ls-files` exits 128 there, and four of the gates shell out to exactly that. So
    the directory gets its own `.git` and the index the export was made FROM is
    copied into it. Nothing is ever committed; the index alone answers ls-files.
    """
    dest = pathlib.Path(dest)
    dest.mkdir(parents=True, exist_ok=True)
    idx = pathlib.Path(scratch) / (dest.name + ".index")
    env = dict(os.environ, GIT_INDEX_FILE=str(idx))

    for args in (["read-tree", tree_sha],
                 ["checkout-index", "-a", "-f",
                  "--prefix=" + dest.as_posix().rstrip("/") + "/"]):
        out = subprocess.run(["git", "-C", str(repo), *args],
                             capture_output=True, text=True, env=env)
        if out.returncode != 0:
            raise RuntimeError(f"export {tree_sha[:12]}: git {args[0]}: "
                               f"{out.stderr.strip()}")

    out = subprocess.run(["git", "init", "-q", str(dest)],
                         capture_output=True, text=True)
    if out.returncode != 0:
        raise RuntimeError(f"export {tree_sha[:12]}: git init: {out.stderr.strip()}")
    shutil.copyfile(idx, dest / ".git" / "index")
    return dest


# --------------------------------------------------------------------------- #
# Running the gates.
# --------------------------------------------------------------------------- #

def run_gate(gate, tree):
    """One gate against one exported tree -> {status, rc, summary, output}."""
    try:
        cmds = gate["commands"](tree)
    except Exception as exc:                       # noqa: BLE001 - report, never crash
        return {"status": "error", "rc": None,
                "summary": f"could not build the command line: {exc}", "output": ""}
    if not cmds:
        return {"status": "error", "rc": None,
                "summary": "no work to do -- refusing to report a pass "
                           "over an empty input set", "output": ""}

    worst, chunks = 0, []
    for argv in cmds:
        try:
            out = subprocess.run(argv, cwd=str(tree), capture_output=True,
                                 text=True, errors="replace", timeout=GATE_TIMEOUT)
        except subprocess.TimeoutExpired:
            return {"status": "error", "rc": None,
                    "summary": f"timed out after {GATE_TIMEOUT}s", "output": ""}
        except OSError as exc:
            return {"status": "error", "rc": None,
                    "summary": f"could not run: {exc}", "output": ""}
        chunks.append((out.stdout or "") + (out.stderr or ""))
        worst = max(worst, out.returncode)

    text = "\n".join(c for c in chunks if c.strip())
    lines = [ln for ln in text.splitlines() if ln.strip()]
    status = "pass" if worst == 0 else ("fail" if worst == 1 else "error")
    return {"status": status, "rc": worst,
            "summary": summarise(lines, status), "output": text}


# The line a reader wants when a gate goes red. The LAST line is right for a gate
# that ends with a verdict (`CONVERTED backslide: ...`, `check_src_tu: N unresolved`)
# and useless for a batched one -- header-offsets ends on whichever header happened
# to sort last, which says nothing about why it failed. So on a red gate the first
# line that looks like the complaint wins, and the last line is the fallback.
_COMPLAINT = re.compile(
    r"FAIL|REFUS|ERROR|backslide|unresolved|DUPLICATE|TOO SMALL|"
    r"do(es)? not (exist|resolve)|[1-9]\d* mismatched", re.I)


def summarise(lines, status):
    if not lines:
        return "(no output)"
    if status != "pass":
        for ln in lines:
            if _COMPLAINT.search(ln):
                return ln.strip()[:200]
    return lines[-1].strip()[:200]


def run_all_gates(tree):
    return {g["key"]: run_gate(g, tree) for g in GATES}


def coverage_metrics(tree):
    """source_coverage.py --json on a tree, or None if it could not be measured."""
    try:
        out = subprocess.run([sys.executable, "tools/source_coverage.py", "--json"],
                             cwd=str(tree), capture_output=True, text=True,
                             errors="replace", timeout=GATE_TIMEOUT)
    except (OSError, subprocess.TimeoutExpired):
        return None
    if out.returncode != 0:
        return None
    try:
        return json.loads(out.stdout)
    except ValueError:
        return None


# --------------------------------------------------------------------------- #
# Reporting.
# --------------------------------------------------------------------------- #

def print_table(rows, cov_lines, cov_measured, say=print, cov_context=()):
    width = max([len(r["gate"]) for r in rows] + [len(COVERAGE_GATE), 18])
    say(f"  {'gate'.ljust(width)}  {'base':<7}  {'merge':<7}  verdict")
    say(f"  {'-' * width}  {'-' * 7}  {'-' * 7}  {'-' * 12}")
    for r in rows:
        say(f"  {r['gate'].ljust(width)}  {r['base']:<7}  {r['merge']:<7}  "
            f"{r['verdict']}")
    if cov_measured:
        cov_verdict = "REGRESSION" if cov_lines else "ok"
        say(f"  {COVERAGE_GATE.ljust(width)}  {'(ref)':<7}  "
            f"{'FAIL' if cov_lines else 'pass':<7}  {cov_verdict}")
        for line in cov_lines:
            say(f"  {' ' * width}      {line}")
        for line in cov_context:
            say(f"  {' ' * width}      info: {line}")
    else:
        say(f"  {COVERAGE_GATE.ljust(width)}  {'(ref)':<7}  {'error':<7}  "
            f"not measured on both trees -- see above")


def main(argv=None):
    ap = argparse.ArgumentParser(
        description=__doc__.splitlines()[0],
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="Advisory. Nothing in .github/workflows/ runs this; it is a command "
               "you run before you press merge.")
    ap.add_argument("targets", nargs="+", metavar="PR|SHA",
                    help="PR numbers (resolved through `gh`) and/or commit-ishes")
    ap.add_argument("--base", default="origin/main", metavar="REF",
                    help="the ref the merge is computed against (default origin/main)")
    ap.add_argument("--json", action="store_true", help="emit the report as JSON")
    ap.add_argument("--keep-trees", action="store_true",
                    help="leave the exported trees on disk and print their paths")
    ap.add_argument("--repo", default=str(REPO), metavar="PATH",
                    help="repository to read (default: this file's repo)")
    ap.add_argument("--tmp", default=None, metavar="DIR",
                    help="where to export trees (default: a system temp dir)")
    ap.add_argument("--fetch", action="store_true",
                    help="fetch a PR head that is not in the local object store "
                         "(`git fetch origin pull/N/head`). Off by default: a tool "
                         "that reads should not touch the network, or the object "
                         "store, unless asked")
    args = ap.parse_args(argv)

    try:
        sys.stdout.reconfigure(encoding="utf-8")
    except Exception:
        pass

    # --json means the caller is a program. The narrative goes away entirely rather
    # than being interleaved with the document, so `| jq` works without a --quiet.
    def say(*a, **k):
        # Flushed: a run is minutes long and its output is usually redirected to a
        # file or a PR body. A block buffer would show nothing at all until the end.
        if not args.json:
            print(*a, flush=True, **k)

    repo = pathlib.Path(args.repo)
    if git(repo, "rev-parse", "--git-dir").returncode != 0:
        print(f"{repo} is not a git repository", file=sys.stderr)
        return 2
    if not git_supports_write_tree(repo):
        print("this git has no `merge-tree --write-tree` (needs git >= 2.38).\n"
              "  Without it there is no way to compute a merge result without "
              "checking one out,\n  and checking one out is exactly what this tool "
              "exists to avoid.", file=sys.stderr)
        return 2

    base_out = git(repo, "rev-parse", args.base + "^{commit}")
    if base_out.returncode != 0:
        print(f"base ref {args.base!r} does not resolve. Try `git fetch origin`.",
              file=sys.stderr)
        return 2
    base_sha = base_out.stdout.strip()

    # Resolve every target BEFORE exporting anything: a typo on the third argument
    # should not cost a 90-second base export first.
    targets = []
    for spec in args.targets:
        if is_pr_number(spec):
            try:
                sha, label = resolve_pr(spec)
            except ValueError as exc:
                print(str(exc), file=sys.stderr)
                return 2
            # `gh` knows the head sha; this clone may not have the object. Say so
            # precisely, with the command that fixes it, rather than letting
            # merge-tree fail with "not something we can merge".
            num = spec.strip().lstrip("#")
            if git(repo, "cat-file", "-e", sha + "^{commit}").returncode != 0:
                if not args.fetch:
                    print(f"PR #{num}'s head {sha[:12]} is not in this repository's "
                          f"object store.\n"
                          f"  Fetch it, or re-run with --fetch:\n"
                          f"    git -C {repo} fetch origin pull/{num}/head",
                          file=sys.stderr)
                    return 2
                f = git(repo, "fetch", "--quiet", "origin", f"pull/{num}/head")
                if f.returncode != 0 or git(
                        repo, "cat-file", "-e", sha + "^{commit}").returncode != 0:
                    print(f"could not fetch PR #{num}'s head: "
                          f"{(f.stderr or '').strip()}", file=sys.stderr)
                    return 2
        else:
            out = git(repo, "rev-parse", spec + "^{commit}")
            if out.returncode != 0:
                print(f"{spec!r} is neither a PR number nor a commit-ish that "
                      f"resolves here.", file=sys.stderr)
                return 2
            sha, label = out.stdout.strip(), spec
        targets.append({"spec": spec, "label": label, "head": sha})

    scratch = pathlib.Path(args.tmp) if args.tmp else pathlib.Path(
        tempfile.mkdtemp(prefix="premerge-"))
    scratch.mkdir(parents=True, exist_ok=True)
    made = []
    report = {"base": {"ref": args.base, "sha": base_sha}, "targets": []}
    exit_code = 0

    def cleanup():
        if args.keep_trees:
            return
        for path in made:
            shutil.rmtree(path, ignore_errors=True)   # never git's own remover
            try:
                (scratch / (pathlib.Path(path).name + ".index")).unlink()
            except OSError:
                pass
        if not args.tmp:
            shutil.rmtree(scratch, ignore_errors=True)

    try:
        base_tree_sha = git(repo, "rev-parse", base_sha + "^{tree}").stdout.strip()
        say(f"base   {args.base} @ {base_sha[:12]}")
        try:
            base_dir = export_tree(repo, base_tree_sha, scratch / "base", scratch)
        except RuntimeError as exc:
            print(str(exc), file=sys.stderr)
            cleanup()
            return 2
        made.append(base_dir)

        # Once, and reused by every target. This is why several PRs in one run costs
        # far less than the same PRs one at a time.
        base_verdicts = run_all_gates(base_dir)
        base_cov = coverage_metrics(base_dir)
        report["base"]["gates"] = {k: {kk: v[kk] for kk in ("status", "rc", "summary")}
                                   for k, v in base_verdicts.items()}
        report["base"]["coverage"] = base_cov
        already_red = [k for k, v in base_verdicts.items() if v["status"] != "pass"]
        if already_red:
            say(f"       NOTE: {len(already_red)} gate(s) already red on the base "
                  f"({', '.join(already_red)}).")
            say(f"       Those are not any PR's to own and cannot fail this run.")
        say()

        conflicted = 0
        for t in targets:
            say(f"target {t['label']}  head {t['head'][:12]}")
            mt = subprocess.run(["git", "-C", str(repo), "merge-tree", "--write-tree",
                                 base_sha, t["head"]], capture_output=True, text=True)
            tree_sha, conflicts = parse_merge_tree(mt.returncode, mt.stdout)
            if conflicts is None:
                msg = (mt.stderr or "").strip() or f"git exited {mt.returncode}"
                say(f"  TOOL ERROR: git merge-tree could not answer: {msg}\n")
                t.update(outcome="error", detail=msg)
                report["targets"].append(t)
                exit_code = max(exit_code, 2)
                continue
            if conflicts:
                # Its own outcome, deliberately: there is no merge result to gate.
                say(f"  CONFLICT: this branch does not merge into "
                      f"{args.base} cleanly.")
                for line in conflicts[:12]:
                    say(f"      {line}")
                say("  No gates run -- there is no merge result to run them on. "
                      "Rebase first.\n")
                t.update(outcome="conflict", detail=conflicts)
                report["targets"].append(t)
                conflicted += 1
                continue

            try:
                d = export_tree(repo, tree_sha,
                                scratch / f"merge-{t['head'][:12]}", scratch)
            except RuntimeError as exc:
                say(f"  TOOL ERROR: {exc}\n")
                t.update(outcome="error", detail=str(exc))
                report["targets"].append(t)
                exit_code = max(exit_code, 2)
                continue
            made.append(d)

            merge_verdicts = run_all_gates(d)
            merge_cov = coverage_metrics(d)
            rows = diff_verdicts(base_verdicts, merge_verdicts)
            cov_lines = coverage_regressions(base_cov, merge_cov)
            cov_ctx = coverage_context(base_cov, merge_cov, cov_lines)
            cov_measured = base_cov is not None and merge_cov is not None

            say(f"  merge tree {tree_sha[:12]}")
            print_table(rows, cov_lines, cov_measured, say, cov_ctx)

            regs = regressions(rows)
            for r in regs:
                v = merge_verdicts.get(r["gate"], {})
                say(f"\n  {r['gate']}: green on {args.base}, {r['merge'].upper()} on "
                      f"the merge result.")
                body = (v.get("output") or "").splitlines()
                summary = v.get("summary", "")
                # summarise() often picks out the gate's own headline, which is
                # already the body's first line. Printed twice it reads like two
                # separate findings.
                if summary and (not body or summary != body[0].strip()):
                    say(f"      {summary}")
                for line in body[:25]:
                    say(f"      | {line}")
            if cov_lines:
                regs = regs + [{"gate": COVERAGE_GATE}]
                say(f"\n  {COVERAGE_GATE}: the merge result builds FEWER bytes from "
                      f"source than {args.base}.")

            t.update(outcome="regression" if regs else "clean",
                     mergeTree=tree_sha,
                     gates={k: {kk: v[kk] for kk in ("status", "rc", "summary")}
                            for k, v in merge_verdicts.items()},
                     coverage=merge_cov,
                     coverageRegressions=cov_lines,
                     coverageContext=cov_ctx,
                     rows=rows)
            report["targets"].append(t)

            if regs:
                exit_code = max(exit_code, 1)
                say(f"\n  RESULT: {len(regs)} gate(s) go green -> red on the merge "
                      f"result. This PR is answerable for them.\n")
            else:
                say(f"\n  RESULT: nothing goes green -> red. Safe to merge as far as "
                      f"the STATIC gates can tell -- no ROM was built.\n")

        if conflicted and exit_code == 0:
            exit_code = 3
    finally:
        if args.keep_trees:
            for path in made:
                print(f"kept: {path}", file=sys.stderr)
        cleanup()

    report["exit"] = exit_code
    if args.json:
        print(json.dumps(report, indent=2, sort_keys=True))
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
