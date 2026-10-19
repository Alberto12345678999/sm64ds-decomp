# Handoff: tools-elf-longnames1017

This commit permits descriptive manifest aliases that are longer than compiler
symbols, such as an anonymous member-pointer constant named `@1614`. The existing
rename operation previously refused those aliases before the TU could link.

## Identity and next action

- Issue: https://github.com/tangosdev/sm64ds-decomp/issues/4021
- Task/stage: `tools-elf-longnames1017`, `produce`.
- Session/harness: `codex-elf-longnames-producer1017`, Codex.
- Branch: `refs/heads/tools/elf-symbol-name-growth`.
- Source, workflow and accepted input: `e8dc126bcda1865cce7a4a4cb920fb2095deefb9`.
- Status: tooling candidate; independent review/verification and PR publication
  remain pending. The queue records this commit's immutable SHA.
- Next role: independent verifier. After acceptance, the Memory2 producer can
  consume this dependency and rerun its TU and ROM gates.
- Reserved files changed: `tools/objisolate.py`, `tools/test_objisolate.py`,
  `tools/test_owned_function_renames.py`, and this handoff. No source, manifest,
  symbol registry, delinks range, or shared header changes.

## Implementation and limits

Fitting aliases retain the existing in-place rewrite and shared-suffix refusal.
Longer aliases use the existing validated `_grow_string_table` helper, preserving
old strings and shifting subsequent file offsets with their required alignment.
The rename operation then updates only the selected symbols' `st_name` fields at
the relocated symbol-table offset. All symbols retain their indices, section
indices, values, sizes, bindings and types. Relocation records and code/data bytes
remain unchanged. Simultaneous swaps/chains remain supported; collisions with
unmoved names and duplicate destinations are refused. NUL-containing aliases are
explicitly refused. Growth inherits the helper's ELF32 relocatable-object and
ordinary-header restrictions.

This operation applies names already licensed by the caller. It does not establish
the proposed names' historical authenticity, type correctness, original TU owner,
or ROM correctness, and does not bypass the manifest's existing policy checks.

## Producer checks

All commands ran in the wired private worktree `C:/tmp/sm64ds-objnames1017`.

- `python -m pytest -q tools/test_objisolate.py tools/test_owned_function_renames.py
  tools/test_rombuild.py tools/test_tu_production.py tools/test_canonical_duplicates.py`:
  exit 0, **162 passed, 1 skipped**. Includes actual pinned mwcc objects, longer
  defined/undefined names, mixed-length swaps/chains, shared suffix preservation,
  collisions, malformed growth headers, and existing shorter-name regressions.
  Local logs: `build/longnames-tests.txt`, `build/longnames-tests.xml`.
- `python -m pytest -q tools/test_tubuild.py`: exit 1, **66 passed, 1 skipped,
  9 failed**. Repeated with untouched base `objisolate.py`: all nine failures have
  identical diagnostics. Four require missing local generated RTTI/TU maps;
  five are stale PoleLift, OneUpLogo, LevelObjects and RcCarpet expectations.
  No failing assertion differs between base and candidate. Local comparison:
  `build/tubuild-control-comparison.json`; logs/XML: `build/tubuild-base.*` and
  `build/tubuild-candidate.*`. Candidate restored after the control.
- Actual Memory2 producer object `build/memory2-native/candidate.o` from the sibling
  source worktree: **29 aliases pass**, with 311 symbol indices, 193 sections,
  and all 82 relocation sections preserved. Every non-name symbol field,
  code/data/relocation payload, index and link is unchanged; original string-table
  prefix retained; input file unchanged. Input SHA256:
  `320e117a2088d592f0c3b4079ec55328e97a9a26c4fe4ba7feaf700afcb74f17`.
  Output SHA256: `e8311b78fe140da9e3c77b9925caa0f37783ee29ce94d920d479f0d871620eab`.
  File size grows from 34280 to 35188 bytes. Ignored local reproducer and report:
  `build/verify-memory2-longnames.py`, `build/memory2-longnames-proof.json`.
- `git diff --check`: exit 0.
- No full-ROM or source relocation gate claimed for this tooling-only commit.
  The separate Memory2 source candidate must pass those gates after consuming an
  independently accepted tool dependency. Private validation and PR CI pending.

All compiler objects, private receipts and generated reports remain ignored local
artifacts. The committed tests are reproducible without those private objects;
compiler-backed tests additionally require the pinned mwcc toolchain.
