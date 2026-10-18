# Handoff: tools-initialized-start-aliases1017

This document describes this commit. The queue records its immutable output SHA.

- Issue: [#4041](https://github.com/tangosdev/sm64ds-decomp/issues/4041).
- Producer: `codex-initialized-start-aliases1017` (Codex).
- Branch: `refs/heads/tools/initialized-start-aliases`.
- Accepted dependency/base: `272e5e5b95ef1e028dfb5b9c22ec4e03fc9cdb80` (PR #4036).
- Activated workflow: `18af52b49b9fb5663d417bdfa86109b7b157aaa3`.
- Independent verifier and final PR publication: parent campaign integrator;
  both remain pending at producer handoff. No merge is authorized.

## Scope and behavior

A configured initialized-data name can now alias the start of one actual
compiler-defined object. This retains names such as Amida's
`data_ov006_0213b918`, which shares the native vtable's public address and still
has a declaration in a separately reserved shared header. The alias does not
need a fabricated source reference or additional storage.

The existing proof remains required: one configured module home, one nonlocal
PROGBITS OBJECT definition, the matching complete source provider, the correct
.data/.rodata section, and full coverage of its actual emitted extent. An alias's
explicit extent must fit that object. Defined aliases, ambiguous owners/modules,
duplicate definitions, wrong providers, and uncovered extents remain excluded.
Only initialized storage admits the start address; BSS retains its strict
interior policy. The LCF defines the alias inside its own output module and does
not alter object bytes.

The three reserved files are the helper, its tests, and this handoff. No source,
manifest, overlay configuration, shared header, ROM, compiler, or private receipt
is included. This tool change establishes no new Amida production ownership.

## Proof

- `python -m pytest tools/test_lcf_interior.py tools/test_objisolate.py tools/test_rombuild.py tools/test_rombuild_check.py -q`:
  143 passed. Six added tests cover unimported start aliases for both initialized
  sections, object/alias extents, complete ownership, provider and module identity,
  duplicate/ambiguous owners, existing definitions, kinds, and unchanged BSS policy.
- Private real-object fixture: `build/probe-amida-alias.py` and
  `build/amida-alias-fixture/report.json`. A fresh pinned b56 compile exactly
  equals the frozen readable Amida scout object, SHA256
  `951d1537394fc3379c4f3b75466d9f6cb2e7c7eeaf17adba93bab1bedaf54209`.
  The supported vtable rebias prepares the public symbol at section offset 8 with
  size 148, from the complete 156-byte compiler storage. The accepted base emits
  no numeric alias; this change emits the alias at 0x0213b918 with offset 0.
  Both prepared-object bytes and the source probe remain unchanged.
  Prepared-object SHA256:
  `fc192e4f47ef7b70754cfcdc9c5cd7ea0d4614af172dfb41d8040e6d452da955`.
- The complete read-only Amida scout is preserved privately under the PR #4015
  worktree's `build/data-campaign/amida-native-scout1017/`: eight native objects,
  407 bytes plus one alignment byte, 42 relocations, and 30 functions/344 relocations
  unchanged. This is native feasibility evidence, not an Amida source acceptance.
- `python tools/rombuild.py -j16 --report-json build/tool-production.json`: PASS.
  Fresh stock control and normal production both produce the full 16 MiB retail ROM
  SHA256 `d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`.
  Production reproduces 106/106 modules, 11334 functions, 338 data claims and 245 BSS
  claims (31216 bytes), with zero new strict-symbol errors against nine baseline
  diagnostics. All tested tool inputs remained byte-identical through the run.
  Broad optional ROM-data diagnostics still report one unrelated differing symbol;
  this is not a claim that the whole optional catalog is green.
- Dead-reference check: no new dead references and no broken markdown links.
  Committed whitespace is checked before the immutable queue offer.

## Next action and limits

Independently review this exact tool candidate against the accepted dependency,
rerun the focused suite and real-object fixture, then publish the separate tooling
PR. Amida source may consume the tool only after acceptance and after obtaining
its own source/config reservation. Original Amida source grouping, factory return
signature recovery, existing method/compiler floors, and the remaining global
backlog are outside this tooling task; none is declared complete here.
