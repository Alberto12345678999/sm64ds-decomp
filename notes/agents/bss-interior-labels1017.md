# Compiler-owned BSS interior labels

Task `tools-bss-interiors1017`, issue #4034. Producer session
`codex-bss-interiors1017`; independent verification is required before publication.

The native baby-penguin initializer builds six state pairs in one 96-byte array.
The final update field has an existing configured label 88 bytes into that array.
The array ends at `ov072:0x02122dcc`, before 20 bytes of module alignment padding.
The existing terminal-boundary check rejects any interior label, and the older
BSS alias helper requires a live import. Native array expressions use base plus
offset, so the retained labels need identities even when no object imports them.

The terminal rule now permits an explicitly zero-sized BSS alias strictly inside
the independently sized final object. It still rejects unsized or positive-sized
interior records, duplicate names/addresses, separately emitted or manifest-owned
objects, and symbols or owners in the alignment tail. A zero-sized alias cannot
establish the terminal boundary or replace the positive-sized parent.

This distinction matters to the actual linker. A 96-byte parent plus an eight-byte
interior record makes DSD emit overlapping symbol sizes, which mwldarm rejects in
the zero-source control. The parent remains 96 bytes; the interior identity uses
`kind:bss(size=0x0)`. Its source member is still eight bytes wide. The corrected
zero-source configuration links and produces the exact retail ROM. No padding
object or extra storage is introduced.

`lcf_interior` reuses the initialized-storage provenance checks for NOBITS storage:
ELF32 little-endian ARM relocatable input, one non-local OBJECT definition, actual
section extent, unique configured module home, and a complete matching source
provider. Missing interior labels are defined in their output module even without
imports. Existing imported BSS and fixed-address code handling remain available.
The input object is unchanged. These aliases preserve identity; they do not prove
the source type, member width, initializer behavior or original identifier.

## Dependency composition

The review base is `e2a4ac2b61602d3e48e44404d1bf7c57418c6b3a`, published as
`refs/heads/tools/data-foundation1017`. It composes independently accepted PR #4024 tip
`2801e012eea47be85d78732b81ff32c3df84e2fb` and PR #4025 tip
`121ca67be3ac06751cc6d8106ff6487a76dc52fd` without conflicts. The original queue
input is the latter tip. This composition supplies both longer compiler-local
symbol names and initialized-data interior labels. Neither PR nor main was merged.
The BSS PR is reviewed against the composition so its diff contains only this
tooling change. Source issue #4032's continuation will depend on the accepted BSS tip.

## Producer evidence

- Dependency composition: 134 focused tests pass before this change.
- Candidate: 146 focused tests pass across interior-label, terminal-BSS,
  object-isolation and owned-function-rename suites. Tests exercise zero-storage
  aliases and reject overlap, invalid owner sizes, wrong providers/modules,
  incomplete ranges, duplicate definitions and incompatible ELF inputs.
- Six owned-relocation negative-verdict tests also pass; the relocation decision
  ladder is unchanged.
- Actual baby-penguin prepared object SHA256
  `c58fe49a1acee22026cfd45bed4d99c8d32818aab4ab48f84f025236a7130c79`:
  all five non-text sections and 70 relocations pass the candidate verifier.
  Five BSS identities are recovered: `0x02122cf0`, `0x02122d48`, `0x02122d54`,
  `0x02122d60`, `0x02122dc4`. Object bytes are unchanged.
- The fixture uses the source producer's frozen configuration and object, not
  independent source acceptance. Its reduced object list also triggers existing
  fixed-address code aliases because other production objects are absent.
- Private artifacts: `build/bss-interior-tests.log`,
  `build/verify-actual-bss-fixture.py`, `build/actual-bss-fixture-report.json`.

Independent review must exercise a fresh actual production link, confirm the
zero-source control and exact module/ROM output, and inspect both positive and
negative cases. The source reconstruction remains a separate review. No ROM,
compiler input, private queue receipt or generated object is committed.
