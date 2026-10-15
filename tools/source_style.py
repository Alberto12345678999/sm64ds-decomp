#!/usr/bin/env python3
"""Changed-code formatting and source-pattern regression check; see notes/source-style.md.

This is not a C++ parser or a byte/relocation validator. No files are rewritten.
With --base, compare its merge base with HEAD to the working tree (including new
untracked src/include files). Renames retain their original pattern debt.
Without --base, explicit --files are checked in full, useful for fixtures.
"""
import argparse
import collections
import difflib
import json
import os
import pathlib
import re
import shutil
import subprocess
import sys
import xml.etree.ElementTree as ET
from dataclasses import dataclass

import delaunder
import msvc_arms

ROOT = pathlib.Path(__file__).resolve().parent.parent
FORMAT_VERSION = "19.1.7"
SUFFIXES = {".c", ".cpp", ".h", ".hpp"}
# Deliberately narrow patterns, independent of the published CONVERTED metric.
RULES = {
    "raw-offset": re.compile(
        r"\(\s*(?:(?:unsigned|signed)\s+)?\w+\s*\*\s*\)\s*\(\s*\w+\s*\+\s*0x[0-9a-fA-F]+"
        r"|\(\s*char\s*\*\s*\)\s*[\w()]+\s*\+\s*0x[0-9a-fA-F]+"),
    "manual-vtable": re.compile(r"(?:->|\.)\s*(?:vtable|vptr|vtbl)\s*\[[^\]\n]+\]"),
    "handspelled-member": re.compile(r"\b_ZN\w+"),
    "unknown-field": re.compile(r"\bunk_[0-9a-fA-F]+\b"),
    "modern-nullptr": re.compile(r"\bnullptr\b"),
}


class StyleError(Exception):
    """Missing inputs or unsupported configuration: never a passing check."""


@dataclass(frozen=True)
class Finding:
    rule: str
    line: int
    match: str


def fingerprint(text):
    return re.sub(r"\s+", "", text)


def source_findings(text):
    # mwcc_side retains line numbers. Comments/literals are not source defects.
    text = msvc_arms.mwcc_side(text)
    mask = delaunder.code_mask(text)
    code = "".join(c if mask[i] or c == "\n" else " " for i, c in enumerate(text))
    found = []
    for rule, pattern in RULES.items():
        for m in pattern.finditer(code):
            found.append(Finding(rule, code.count("\n", 0, m.start()) + 1,
                                 fingerprint(m.group())))
    return sorted(found, key=lambda f: (f.line, f.rule))


def new_findings(before, after):
    bank = collections.Counter((f.rule, f.match) for f in source_findings(before))
    out = []
    for f in source_findings(after):
        key = f.rule, f.match
        if bank[key]:
            bank[key] -= 1
        else:
            out.append(f)
    return out


def added_ranges(before, after):
    old, new = before.splitlines(), after.splitlines()
    return [(j1 + 1, j2) for tag, _i1, _i2, j1, j2 in
            difflib.SequenceMatcher(None, old, new, autojunk=False).get_opcodes()
            if tag != "equal" and j2 > j1]


def git(root, *args, optional=False):
    p = subprocess.run(["git", "-C", str(root), *args], capture_output=True)
    if p.returncode and not optional:
        raise StyleError(p.stderr.decode("utf-8", errors="replace").strip())
    return p


def in_scope(path):
    p = pathlib.PurePosixPath(path)
    return (not any(c in path for c in "*?[]\\") and not p.is_absolute()
            and ".." not in p.parts and p.parts
            and p.parts[0] in {"src", "include"} and p.suffix in SUFFIXES)


def changed_paths(root, base):
    """Return (new path, original path) pairs, preserving rename identity."""
    raw = git(root, "diff", "--name-status", "-z", "--find-renames", base,
              "--", "src", "include").stdout.decode("utf-8").split("\0")
    pairs, i = {}, 0
    while i < len(raw) and raw[i]:
        status, path = raw[i:i + 2]
        i += 2
        old = path
        if status.startswith(("R", "C")):
            path = raw[i]
            i += 1
        if not status.startswith("D") and in_scope(path):
            pairs[path] = old
    extra = git(root, "ls-files", "--others", "--exclude-standard", "-z",
                "--", "src", "include").stdout.decode("utf-8").split("\0")
    for path in extra:
        if in_scope(path):
            pairs[path] = path
    return sorted(pairs.items())


def read_before(root, base, path):
    if base is None:
        return ""
    # A missing path is a new file; any other Git error is fatal.
    exists = git(root, "ls-tree", "-z", base, "--", path).stdout
    if not exists:
        return ""
    return git(root, "show", f"{base}:{path}").stdout.decode("utf-8").replace("\r\n", "\n")


def load_exceptions(path):
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
        if type(data.get("schema")) is not int or data["schema"] != 1 or not isinstance(data.get("exceptions"), list):
            raise ValueError("expected schema 1 and exceptions list")
        out = {}
        for row in data["exceptions"]:
            if set(row) != {"path", "rule", "match", "count", "reason", "evidence"}:
                raise ValueError("exception needs path, rule, match, count, reason, evidence")
            if not in_scope(row["path"]) or row["rule"] not in RULES:
                raise ValueError("unknown exception rule or source path")
            if type(row["count"]) is not int or row["count"] < 1:
                raise ValueError("exception count must be a positive integer")
            for key in ("match", "reason", "evidence"):
                if not isinstance(row[key], str) or not row[key].strip():
                    raise ValueError(f"exception {key} must be nonempty")
            key = row["path"], row["rule"], fingerprint(row["match"])
            if key in out:
                raise ValueError("duplicate exception")
            out[key] = row["count"]
        return out
    except (OSError, ValueError, TypeError, AttributeError) as exc:
        raise StyleError(f"invalid exception file {path}: {exc}") from exc


def apply_exceptions(path, findings, exceptions, before=""):
    # An exception caps the total population, not the increment in each PR.
    existing = collections.Counter((f.rule, f.match) for f in source_findings(before))
    budget = {key: max(0, count - existing[key[1:]])
              for key, count in exceptions.items() if key[0] == path}
    out = []
    for f in findings:
        key = path, f.rule, f.match
        if budget.get(key, 0):
            budget[key] -= 1
        else:
            out.append(f)
    return out


def formatter_version(executable):
    try:
        p = subprocess.run([executable, "--version"], capture_output=True, text=True)
    except OSError as exc:
        raise StyleError(f"cannot run clang-format: {exc}") from exc
    if p.returncode or not re.search(r"\bversion " + re.escape(FORMAT_VERSION) + r"(?![0-9.])", p.stdout):
        raise StyleError(f"need clang-format {FORMAT_VERSION}; got {p.stdout.strip()!r}")


def format_findings(executable, config, path, text, ranges):
    if not ranges:
        return []
    cmd = [executable, "--output-replacements-xml", f"--style=file:{config}",
           "--fallback-style=none", f"--assume-filename={path}"]
    cmd.extend(f"--lines={start}:{end}" for start, end in ranges)
    raw = text.encode("utf-8")
    p = subprocess.run(cmd, input=raw, capture_output=True)
    if p.returncode:
        raise StyleError(p.stderr.decode("utf-8", errors="replace").strip())
    try:
        tree = ET.fromstring(p.stdout)
        if tree.tag != "replacements" or tree.get("incomplete_format") == "true":
            raise ValueError("formatter did not fully parse the requested source")
        out = []
        for row in tree.findall("replacement"):
            offset, length = int(row.attrib["offset"]), int(row.attrib["length"])
            first = raw.count(b"\n", 0, offset) + 1
            last = raw.count(b"\n", 0, offset + length) + 1
            # Whitespace ending at a newline also controls the following line's
            # indentation. Its exclusive endpoint must participate in coverage.
            affected = [max(first, start) for start, end in ranges
                        if first <= end and last >= start]
            if affected:
                out.append(Finding("format", min(affected), "run the pinned formatter on these lines"))
        return out
    except (ET.ParseError, ValueError, KeyError) as exc:
        raise StyleError(f"invalid formatter result for {path}: {exc}") from exc


def check(root, base, files, executable, patterns_only=False):
    exceptions = load_exceptions(root / "config/source-style-exceptions.json")
    if base is not None:
        base = git(root, "merge-base", base, "HEAD").stdout.decode().strip()
    if files is None:
        pairs = changed_paths(root, base)
    else:
        renames = dict(changed_paths(root, base)) if base is not None else {}
        selected = []
        for path in files:
            full = (root / path).resolve()
            if not full.is_relative_to(root.resolve()):
                raise StyleError(f"unsupported path: {path}")
            selected.append(full.relative_to(root.resolve()).as_posix())
        pairs = [(p, renames.get(p, p)) for p in selected]
    if not patterns_only:
        if not executable:
            raise StyleError("clang-format missing; install tools/requirements-style.txt")
        formatter_version(executable)
    results = []
    for path, old in pairs:
        full = (root / path).resolve()
        if not full.is_relative_to(root.resolve()) or full.suffix not in SUFFIXES:
            raise StyleError(f"unsupported path: {path}")
        after = full.read_text(encoding="utf-8")
        before = read_before(root, base, old)
        findings = apply_exceptions(path, new_findings(before, after), exceptions, before)
        ranges = added_ranges(before, after)
        if not patterns_only:
            findings += format_findings(executable, root / ".clang-format", path, after, ranges)
        results.extend({"path": path, "line": f.line, "rule": f.rule, "match": f.match}
                       for f in findings)
    return {"base": base, "files_checked": len(pairs), "patterns_only": patterns_only,
            "findings": results}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", help="compare merge-base with HEAD to the working tree")
    parser.add_argument("--files", nargs="+", help="check explicit files in full, or against --base")
    parser.add_argument("--clang-format", default=os.environ.get("CLANG_FORMAT") or shutil.which("clang-format"))
    parser.add_argument("--patterns-only", action="store_true", help="explicitly omit formatting; not a full style pass")
    parser.add_argument("--json", type=pathlib.Path)
    args = parser.parse_args(argv)
    try:
        report = check(ROOT, args.base or (None if args.files else "origin/main"),
                       args.files, args.clang_format, args.patterns_only)
        if args.json:
            args.json.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        for f in report["findings"]:
            print(f"{f['path']}:{f['line']}: {f['rule']}: {f['match']}")
        print(f"source-style: {report['files_checked']} file(s), {len(report['findings'])} finding(s)"
              + ("; PATTERNS ONLY, formatting not checked" if args.patterns_only else ""))
        return int(bool(report["findings"]))
    except (StyleError, OSError, UnicodeError) as exc:
        print(f"source-style: ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
