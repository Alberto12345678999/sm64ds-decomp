# Sanbo native data

Task `data-sanbo-native1018`, issue [4078](https://github.com/tangosdev/sm64ds-decomp/issues/4078).
The input and tested dependency is `d8e9946bc1f40ece143f28a8dac040f66c40b4fc`.
The active queue workflow is `18af52b49b9fb5663d417bdfa86109b7b157aaa3`.
The queue records the immutable candidate and independent review. No merge is
authorized by this handoff.

## Source and storage

This change assigns the complete ov096 data interval
`[0x02137920, 0x02137a54)` to `src/game/actors/d_a_sanbo.cpp`. It contains 307
bytes of native objects and one natural alignment byte. The existing code,
392-byte static initializer, constructor slot and 136-byte BSS range remain
source-owned. This is an evidenced reconstruction assignment; it does not prove
one unique original source file or recover the original variable names.

| Storage | Native format and evidence |
| --- | --- |
| `02137920..02137980` | Twelve 8-byte native member-pointer literals. Each has the exact state-method relocation and a zero `this` adjustment. |
| `02137980..0213798b` | Compiler type name `9daSanbo_c` and its NUL terminator; the next byte is alignment. |
| `0213798c..02137998` | Three-word single-inheritance RTTI, including the existing `dActor_c` base. |
| `02137998..021379b4` | `SpawnInfo<daSanbo_c>` for the head factory, behavior/render priorities `0xf0/0x5f`. |
| `021379b4..021379d0` | The same shared profile type for the segment factory, priorities `0xf1/0x60`. |
| `021379d0..02137a54` | Full 132-byte native vtable storage: two-word ABI prefix plus 31 slots. The public address point is `021379d8`. |

Both profiles preserve flags `0x10000002`, clip Y offset and radius
`0x1f4000`, and clip/far distances `0x1000000`. Their field definitions come from the existing shared
`SpawnInfo.h`; this change does not invent a local profile layout or edit that
header. The RTTI spelling is recovered from retail. The existing profile and
address-based state symbols remain reconstruction identities.

The runtime array at `02137b48` contains six entry/update pairs. Its initializer
now uses direct member addresses, with no function-address integer blob and no
incompatible member-pointer casts. The compiler emits the twelve constants in
retail order. Exact per-literal compiler-name mappings in the manifest are
supported by method destinations and initializer relocation sites; they retain
the existing configured identities and native local binding. No rename-ledger
entry or fabricated import is introduced.

The existing initializer and constructor-slot binding rewrites remain compatibility
policies for their configured global identities. Their inherited explanation that
DSD cannot encode local symbols was incorrect and is corrected here; explicit
local rows are used for all twelve native descriptors.

| State | Entry descriptor / method | Update descriptor / method |
| --- | --- | --- |
| 0 | `02137948 / 021368a4` | `02137940 / 02136754` |
| 1 | `02137950 / 0213670c` | `02137928 / 021365d4` |
| 2 | `02137930 / 02136534` | `02137920 / 02136434` |
| 3 | `02137978 / 0213640c` | `02137970 / 021363c4` |
| 4 | `02137938 / 021363b4` | `02137968 / 02136264` |
| 5 | `02137960 / 02136134` | `02137958 / 021360c4` |

Eleven existing handlers return `1`. The remaining handler, `0213670c`, already
leaves `r0 = 1` after assigning its state field. Giving it an `int` return and
an explicit `return 1` preserves the complete function bytes. The state-pointer
type now agrees with all twelve handlers, and dispatch still discards results.
This is a consistent reconstructed interface, not proof of the historical
return-type declaration. Only this source consumes the changed class header.

## Ownership and earlier proposals

The live v2 queue granted the class, source, header, manifest, ov096 config and
exact ranges before tracked edits. The adjacent Tor task retains its disjoint
source, manifest and ranges. `decl_common.h`, the shared rename ledger and all
other headers remain unchanged. Existing address-keyed contributor credit is
preserved. The twenty predecessor findings and all current findings are carried
in the experiment record and queue lineage.

[PR 3937](https://github.com/tangosdev/sm64ds-decomp/pull/3937) historically
proposed twelve raw two-word constants for these 96 PMF bytes at head
`4ac26ae9dab80c1880fe5b7cd63abe420771721d`. An initial inspection before fetching
that commit incorrectly inferred that the files were missing; the fetched files
were preserved and that inference was corrected before claiming this task.
The later observed head `6edddc799e744968ada4607ddee3a0e4c0a38c17` removes both
that proposal and its separate 16-byte BSS proposal, together with their delinks.
That separate BSS region is outside this change. PR 3937 was not edited, closed
or rebased. Absence of files is not ownership authority; the successful queue
grant is recorded separately.

## Proof and limitations

The producer's initial fresh pinned object is 22,248 bytes, SHA-256
`28d1d2821c821e1c72ef0fb49d7a6a11be5db56311a89c84081a8da4177fe50a`.
The native candidate preserves all 53 prior definitions, 38 emitted functions
and 230 relocation records after the exact compiler-local descriptor mapping.
The 392-byte initializer and all 22 of its relocation sites remain identical.
All 17 native objects and their 49 data relocation destinations are checked
against retail separately from ordinary function matching.

Standalone verification reports 36/36 matching listed functions and retains its
existing initializer-classification refusal. Complete scratch and default
production, including actual provider provenance, are the required data gates;
their final results are recorded in the experiment and queue evidence. A stock
control's nine existing strict-symbol errors are not a clean symbol check.

The optional raw-data scanner skips local definitions. Its focused report has
seven verified and seven partial records, with no differing record; it does not
measure the twelve local PMFs. The separate full-object relocation proof and
actual linked-provider checks cover those constants and the complete data range.

An initial enrollment draft confused the vtable public extent with full storage
and counted the ABI preamble twice when recording the RTTI relocation target.
Retail comparison caught both metadata errors. The final manifest records full
storage plus explicit address-point bias and the actual public relocation
destination. No source or linker workaround was used.

This is partial class reconstruction. Model-handle wrapper words, some raw or
Fix12 component interfaces, unknown fields and semantic state names remain
unfinished. Original return signatures and original source names are unproven.
The full data interval can be source-provided without claiming these remaining
class questions are resolved.

Final producer gates passed: all five scratch ranges and 72 nontext relocation
sites; all 106 modules and the full 16 MiB ROM; 22 actual source providers
(17 data and five BSS), including full vtable storage checked independently of
its public extent. The ROM SHA-256 is
`d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`.
The nine baseline symbol errors remain, with zero new errors. Default production
input hashes are rechecked against the committed candidate before offering it.
Style, declaration agreement, header offsets (21 fields through `0x3b0`),
manifest conflicts, port references, rename/dead-reference checks and source
coverage pass. Commit-scoped strict relocation results are recorded in the
immutable producer evidence; they remain distinct from independent acceptance.
