"""Check that a push did not change who matched an existing function.

Who matched a function is function-authors.json. The key is the module and the
address, so moving or renaming a source file does not touch it. This script
compares that file with the base revision. Changing an author, or deleting a
line, exits 1. Adding a line for a new match exits 0.

Usage:
  python tools/prepush_attribution.py
  python tools/prepush_attribution.py --base origin/main
"""
import argparse
import json
import pathlib
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
AUTHORS = "function-authors.json"


def load(rev):
    proc = subprocess.run(
        ["git", "show", f"{rev}:{AUTHORS}"], cwd=REPO,
        capture_output=True, text=True, encoding="utf-8")
    if proc.returncode != 0:
        return {}
    raw = proc.stdout
    data = json.loads(raw)
    functions = data.get("functions", {})
    out = {}
    for key, row in functions.items():
        if isinstance(row, dict):
            out[key] = row.get("author")
        else:
            out[key] = row
    return out


def compare(base, head):
    changed, lost, added = [], [], []
    for key in sorted(set(base) & set(head)):
        if base[key] != head[key]:
            changed.append((key, base[key], head[key]))
    for key in sorted(set(base) - set(head)):
        lost.append((key, base[key]))
    for key in sorted(set(head) - set(base)):
        added.append((key, head[key]))
    return changed, lost, added


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--base", default="origin/main")
    ap.add_argument("--head", default="HEAD")
    args = ap.parse_args()
    head = load(args.head)
    changed, lost, added = compare(load(args.base), head)
    for key, before, after in changed:
        print(f"  author changed  {key}  {before} -> {after}")
    for key, author in lost:
        print(f"  author removed  {key}  was {author}")
    print(f"\n{len(head)} recorded, {len(added)} added, "
          f"{len(changed)} changed, {len(lost)} removed")
    if changed or lost:
        print("\nEdit function-authors.json only to add a new match. "
              "Do not change or delete an existing author.")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
