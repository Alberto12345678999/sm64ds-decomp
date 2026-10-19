# Handoff: data-pgbby-native1017

This document describes this commit. The queue records its immutable output SHA.

## Identity and resumption

- Issue: https://github.com/tangosdev/sm64ds-decomp/issues/4032.
- Producer: `codex-pgbby-native1017`, Codex; branch `data/pgbby-native1017`.
- Final source review/production base: `272e5e5b95ef1e028dfb5b9c22ec4e03fc9cdb80`, the independently accepted documentation follow-up to bounded-BSS tooling candidate `a084543c28f219e4e9e2b7187c9a08d54251e544`. The baseline and whole-TU scratch proof ran on `a084543c`; all compiler/tool/source/config inputs are identical across the documentation-only change. Final production/provider proof ran on `272e5e5` with all unrelated serializer-only manifest formatting restored to its exact original bytes. Its base `e2a4ac2b61602d3e48e44404d1bf7c57418c6b3a` composes accepted tooling PRs #4024 and #4025; the BSS continuation is PR #4036. These remain explicit unmerged dependencies; no main or PR merge is authorized.
- Historical queue input/workflow pin: `2801e012eea47be85d78732b81ff32c3df84e2fb`. The source/config bytes were preserved across the tool dependency update, then all final gates were refreshed.
- Predecessor: `issue2410-clipper-restack1015`. All 42 inherited findings remain in queue evidence with their original dispositions. Unrelated historical scopes are unchanged; this slice does not claim fresh verification or completion of them.
- Status: verified producer candidate, partial reconstruction. Next: independent source review by the parent verifier, then PR publication only. Private validation is pending publication.
- Evidence: `notes/experiments/data-pgbby-native1017.json`; private logs and objects are preserved under `C:/tmp/sm64ds-data-pgbby1017/build/`.

## What changed and why

The current genuine `daPgBby_c` TU now defines six typed resource handles, a five-pointer animation table, four `Vector3` carry offsets and six native `State` pairs. Native constructors generate all ten destructor-registration nodes, twelve member-pointer constants, the 756-byte initializer and its constructor-table pointer. The old handwritten initializer source is retired. Existing methods, signatures and shared headers are preserved.

The six complete delinks ranges for `src/game/actors/d_a_pg_bby.cpp` are:

| Section | ov072 half-open range | Purpose |
|---|---|---|
| `.text` | `0x02120c58..0x02121ffc` | Existing actor methods |
| `.rodata` | `0x02122004..0x02122018` | Five animation-handle pointers |
| `.init` | `0x02122414..0x02122708` | Native static initializer |
| `.ctor` | `0x02122714..0x02122718` | Initializer registration pointer |
| `.data` | `0x021229f4..0x02122a54` | Twelve native member-pointer constants |
| `.bss` | `0x02122c94..0x02122dcc` | Six handles, ten lifecycle nodes, vectors and states |

The BSS claim is exactly 312 bytes: 48 for handles, 120 for registration nodes, 48 for vectors and 96 for states. The last state update member at `0x02122dc4` is eight bytes inside the parent array's final element. Its retained config label has zero storage of its own. Giving that label an additional eight-byte object size double-counted storage and failed the actual zero-source linker; the explicit 96-byte parent plus zero-storage alias passes. Five interior identities remain in the linked OV072 section without splitting native objects.

The old DD249 batch `d607aee6cc7415d803300ce3529e665db558d710` is retained as research evidence. Its state-table range stopped eight bytes early, and it omitted earlier handle/node storage. The current modern source was edited directly; that stale candidate was not transplanted.

## Names, types and ownership evidence

The class identity comes from existing ROM RTTI `daPgBby_c` and the baby-penguin profile. Handle names such as `gPenguinBabyDiveAnimationFile` are descriptive reconstructions supported by the asset catalog and actual initializer/consumer correspondence. Runtime asset handles `0x03ff`, `0x0400`, `0x0403`, `0x0405`, `0x0406` and `0x0408` are distinct from NitroFS file IDs; the experiment records both namespaces and paths.

The local wrappers have the measured eight-byte file-handle layout: `u16 fileID`, `u8 numRefs`, padding, and typed file pointer at +4. Constructor/destructor veneers are explicitly mapped to existing retail functions; the shared fieldless `SharedFilePtr` header is unchanged. Existing native state-member declarations already return `int`; no return-signature cast was introduced. Native `Vector3[4]` construction emits the retail's four individual destructor registrations.

The manifest maps compiler-generated local names to existing address identities. These are compiler ABI records, not newly invented original variable names. The old/native/address map is deliberately recorded in this owned experiment and handoff; the reserved global rename ledger and existing address-keyed function credit are untouched. Normal rename-ledger and declaration checks pass.

This is a modern reconstruction assignment supported by complete object layout and retail initializer correspondence. It is not proof of the original filename, unique source spelling, or historical TU boundary. RTTI/type-name/profile/vtable storage at and beyond `0x02122a54` remains outside this new ownership slice. The 20-byte BSS alignment tail `0x02122dcc..0x02122de0` is unclaimed; no padding object was invented.

## Proof and limits

- Fresh native object SHA256: `bbd879a200b5a4d5032ae5451cde5ea99fc9eac84ba0a36729d324f762f23bfa`. All 32 existing methods, plus the duplicate emitted Vector3 destructor, retain exact raw bytes and canonical relocation records.
- The native initializer matches the retained old source's entire 756 raw bytes and all 52 canonical relocation records. Its full relocated contribution also passes the final whole-TU link.
- `tools/tubuild.py verify`: 32/32 methods match with clean relocation destinations; the existing standalone initializer-classification refusal remains. This is not an unrestricted standalone pass.
- Focused `prepush_linkcheck`: 32 methods VERIFIED, initializer BLIND-18, zero blocking failures. The initializer warning is separately covered by complete old/new raw-object and final six-section relocated-link evidence; it is not called a strict per-function pass.
- Fresh source-independent baseline and `tools/tubuild.py linkcheck ov072/daPgBby_c -j16`: all six ranges and all 106 modules exact; full 16 MiB ROM SHA256 `d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`. Nine pre-existing strict-symbol errors occur in both runs, zero new. The strict-symbol command itself is not green.
- Fresh default production build and linked-provider audit: 11,334 functions, 341 complete data claims and all 106 modules reproduce. All 31 requested whole data objects have actual compiled-source providers: one rodata table, twelve member-pointer constants and eighteen BSS objects. The rebuilt ROM has the same hash above. Requested objects are not supplied by ROM-derived replacement storage.
- The optional broad ROM-data diagnostic still reports the pre-existing `_ZTV10dCcAcPos_c` mismatch in the legacy destructor objects. This is not a blanket claim that every optional object-data diagnostic passes.
- Source style: no findings or formatting deferrals. Declaration agreement: no new disagreements or copied header declarations. Port references and rename ledger pass. No shared header was changed. The final staged/committed diff is checked for whitespace, including added evidence files.

Private logs: `build/pgbby-baseline-accepted-tool.log`, `build/pgbby-candidate-accepted-tool.log`, `build/pgbby-final-production.log`, `build/pgbby-data-provenance.json`, `build/pgbby-final-strict.log`, and `build/pgbby-initializer-comparison.json`. Later post-commit validation belongs in queue evidence; this document does not embed its own commit SHA.

## Remaining work

Stable finding `pggbby-state-tail-001` is fixed by the full native 96-byte array. `pgbby-interior-storage-001` is fixed by correct parent/alias storage metadata and the separately accepted tool dependency. `pgbby-native-residual-001` remains deferred on issue #4032: original identifiers and historical TU boundary are unproven; existing Fix12 by-value bridges, address-named methods and the raw model-matrix copy remain, and metadata beyond this slice still needs evidence and source ownership. The issue stays open for that continuation.
