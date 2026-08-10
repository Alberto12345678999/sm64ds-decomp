"""Turn symbols, a worklist, or a nearmiss filter into breakpoint targets.

A target dict is:
    {"name", "addr" (int), "module", "size", "canary" (16 hex chars),
     "instruction_set" (arm/thumb), "breakpoint_kind" (4/2)}

The canary is target_hex[:16] -- the first 8 bytes of the function. On a bp hit
we read 8 bytes at addr and compare; a mismatch means a DIFFERENT overlay is
mapped there (address aliasing) and the hit is discarded. melonDS keeps
breakpoints as a checked PC-list (not a RAM patch), so bps survive overlay
reloads -- residency only affects whether the code runs, i.e. coverage.
"""
import json
import os
import pathlib
import re

REPO = pathlib.Path(__file__).resolve().parents[2]
DB = REPO / "nearmiss" / "db.jsonl"
ARM9_BASE = 0x02004000
_SYM_RE = re.compile(
    r"^(\S+)\s+kind:function\(([^,)]*),?[^)]*size=(0x[0-9a-fA-F]+)\)\s+"
    r"addr:(0x[0-9a-fA-F]+)"
)
_ADDR_RE = re.compile(r"\baddr:(0x[0-9a-fA-F]+)")


def _iter_db(repo=REPO):
    db = pathlib.Path(repo) / "nearmiss" / "db.jsonl"
    if not db.is_file():
        return
    for line in db.read_text(encoding="utf-8", errors="replace").splitlines():
        if not line.strip():
            continue
        try:
            yield json.loads(line)
        except json.JSONDecodeError:
            continue


def _target(r):
    instruction_set = r.get("instruction_set", r.get("mode", "arm")).lower()
    return {
        "name": r["name"],
        "addr": int(str(r["addr"]), 16),
        "module": r.get("module", "arm9"),
        "size": r.get("size"),
        "canary": r["target_hex"][:16].lower(),
        "canary_source": "nearmiss",
        "instruction_set": instruction_set,
        "breakpoint_kind": 2 if instruction_set == "thumb" else 4,
    }


def find_extracted(repo=REPO):
    """Find gitignored ROM extracts from a worktree or its primary checkout.

    Linked worktrees do not contain ``extracted/``.  They do contain a ``.git``
    file pointing into the primary checkout, which gives us a deterministic and
    developer-path-free fallback.  ``SM64DS_EXTRACTED`` remains the explicit
    override for unusual layouts.
    """
    repo = pathlib.Path(repo).resolve()
    candidates = []
    env = os.environ.get("SM64DS_EXTRACTED")
    if env:
        candidates.append(pathlib.Path(env))
    candidates.append(repo / "extracted")

    git_marker = repo / ".git"
    if git_marker.is_file():
        try:
            line = git_marker.read_text(encoding="utf-8", errors="replace").strip()
            if line.lower().startswith("gitdir:"):
                gitdir = pathlib.Path(line.split(":", 1)[1].strip())
                if not gitdir.is_absolute():
                    gitdir = (repo / gitdir).resolve()
                # <primary>/.git/worktrees/<name> -> <primary>/extracted
                if gitdir.parent.name == "worktrees":
                    candidates.append(gitdir.parent.parent.parent / "extracted")
        except OSError:
            pass

    seen = set()
    for candidate in candidates:
        candidate = candidate.resolve()
        if candidate in seen:
            continue
        seen.add(candidate)
        if (candidate / "arm9_dec.bin").is_file():
            return candidate
    return None


def _symbol_sources(repo, extracted):
    """Yield ``(module, symbols_path, blob_path, base)`` sources."""
    repo = pathlib.Path(repo)
    cfg = repo / "config" / "arm9"
    yield "arm9", cfg / "symbols.txt", extracted / "arm9_dec.bin", ARM9_BASE

    for module in ("itcm", "dtcm"):
        sf = cfg / module / "symbols.txt"
        blobs = [
            repo / "build" / "build" / f"{module}.bin",
            extracted / "dsd" / "arm9" / f"{module}.bin",
            extracted.parent / "build" / "build" / f"{module}.bin",
        ]
        blob = next((p for p in blobs if p.is_file()), blobs[0])
        yield module, sf, blob, None

    ovdir = cfg / "overlays"
    if ovdir.is_dir():
        for d in sorted(ovdir.glob("ov*")):
            yield (d.name, d / "symbols.txt",
                   extracted / "overlays" / f"overlay_{int(d.name[2:]):04d}.bin",
                   None)


def _module_base(symbols, fixed_base=None):
    """Return the config-space module base used by the module registry.

    Overlay and autoload binaries start at their lowest configured symbol, which
    may be data rather than a function.  Deriving the base from function records
    alone shifts every canary when data precedes the first function.
    """
    if fixed_base is not None:
        return fixed_base
    addresses = []
    for line in symbols.read_text(encoding="utf-8", errors="replace").splitlines():
        match = _ADDR_RE.search(line)
        if match:
            addresses.append(int(match.group(1), 16))
    return min(addresses) if addresses else None


def _configured_targets(repo=REPO, extracted=None):
    """Configured functions with ROM-backed canaries, grouped by symbol name."""
    extracted = pathlib.Path(extracted) if extracted else find_extracted(repo)
    if extracted is None:
        return {}

    by_name = {}
    for module, symbols, blob_path, fixed_base in _symbol_sources(repo, extracted):
        if not (symbols.is_file() and blob_path.is_file()):
            continue
        records = []
        for line in symbols.read_text(encoding="utf-8", errors="replace").splitlines():
            m = _SYM_RE.match(line.strip())
            if m:
                records.append((m.group(1), m.group(2).lower(),
                                int(m.group(4), 16), int(m.group(3), 16)))
        if not records:
            continue
        base = _module_base(symbols, fixed_base)
        if base is None:
            continue
        blob = blob_path.read_bytes()
        for name, instruction_set, addr, size in records:
            off = addr - base
            if off < 0 or off + 8 > len(blob):
                continue
            by_name.setdefault(name, []).append({
                "name": name,
                "addr": addr,
                "module": module,
                "size": size,
                "canary": blob[off:off + 8].hex(),
                "canary_source": "rom",
                "instruction_set": instruction_set,
                "breakpoint_kind": 2 if instruction_set == "thumb" else 4,
            })
    return by_name


def from_names(names, repo=REPO, extracted=None):
    """Targets for explicit names, including already-matched config symbols.

    Near-miss records remain the cheapest source because they carry their own
    target bytes.  For matched/readable-C++ functions, fall back to the config
    symbol tables and ROM extracts.  Ambiguous names are reported as missing;
    callers can disambiguate by passing ``module:name``.
    """
    want = []
    seen = set()
    for raw in names:
        name = raw.strip()
        if name and name not in seen:
            want.append(name)
            seen.add(name)
    by_name = {r["name"]: r for r in _iter_db(repo)}
    configured = None
    out, missing = [], []
    for requested in want:
        module, sep, name = requested.partition(":")
        if not sep:
            module, name = None, requested
        if module is None and name in by_name:
            out.append(_target(by_name[name]))
            continue

        if configured is None:
            configured = _configured_targets(repo, extracted)
        candidates = configured.get(name, [])
        if module is not None:
            candidates = [t for t in candidates if t["module"] == module]
        if len(candidates) == 1:
            out.append(candidates[0])
        else:
            missing.append(requested)
    return out, missing


def from_worklist(path):
    """Read names from a worklist file: one per line, or a JSON list, or a
    JSONL of records with a 'name' field. '#' comments and blanks ignored."""
    text = pathlib.Path(path).read_text(encoding="utf-8", errors="replace").strip()
    names = []
    if text.startswith("["):
        for item in json.loads(text):
            names.append(item if isinstance(item, str) else item.get("name"))
    else:
        for line in text.splitlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            if line.startswith("{"):
                try:
                    names.append(json.loads(line).get("name"))
                    continue
                except json.JSONDecodeError:
                    pass
            names.append(line.split()[0])
    return from_names([n for n in names if n])


def from_nearmiss(min_div=None, module=None, limit=None):
    """Targets straight from the nearmiss DB, filtered."""
    out = []
    for r in _iter_db():
        if min_div is not None and r.get("divergences", 0) < min_div:
            continue
        if module is not None and r.get("module", "arm9") != module:
            continue
        out.append(_target(r))
    # densest-first so a fixed run captures the highest-divergence funcs earliest
    out.sort(key=lambda t: -(t["size"] or 0))
    if limit:
        out = out[:limit]
    return out


def group_by_module(targets):
    g = {}
    for t in targets:
        g.setdefault(t["module"], []).append(t)
    return g
