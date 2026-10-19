# Title level-selection data

This commit makes the existing title scene TU provide 1,256 bytes in ov003:
the 54-row table at `[0x020b117c,0x020b132c)` and its native string literals,
profile and compiler metadata at `[0x020b1360,0x020b1698)`. All 59 objects
come from ordinary C++ initializers or compiler ABI emission. No ROM byte
payload or extra padding objects are introduced. Class completion remains partial.

Task `data-title-native1017`, issue #4052, workflow
`18af52b49b9fb5663d417bdfa86109b7b157aaa3`, tested base `1b98141e598440a0432317b58678f3c5c088d558`.
The initial input was the accepted PR4043 helper at
`32c71fc636ce4d11f8150e2af0b6498cb5bcecff`; the separate alignment-tool
dependency models the real linker's `ALIGNALL(4)` semantics. Parent campaign
root independently reviews the immutable source candidate and publishes its PR.

Each eight-byte `TitleLevelEntry` has a name pointer, signed level ID and
unsigned entrance ID, followed by two natural padding bytes. The printer reads
the name; Behavior dispatches level IDs 0 through 51 or the special -2/-1 entries.
The load routine forwards the second byte to the entrance-index consumer;
it is not the independently iterated area index. All 54 entrance values and
both unused bytes are zero in the cartridge. Names and fields are inferred;
the displayed strings and RTTI class identity are direct ROM facts.

`data_ov003_020b117c` becomes `sTitleLevelEntries`. The 54 compiler-generated
literal names are bound to existing numeric labels by exact text, row
relocation, size and emitted order. Their original source identifiers are
unknown. Their numeric config entries now carry the native `local` binding:
`dsd apply` independently prescribed exactly these 54 changes, and each literal
has one own-table reference with no external consumer. Existing global
rename-ledger chains and address-keyed credit stay
unchanged; the full old/native/address map is in the experiment. Native
literal pooling remains compiler-owned; no 54 invented global strings are added.

The profile uses `BaseSpawnInfo<dScTitle_c>`: the factory and priorities 2/4.
The compiler owns the 12-byte RTTI, 13-byte name string and 80-byte vtable
(storage 0x020b1648, public address 0x020b1650). The existing labels at row+4,
row+5 and the vtable public address remain zero-size aliases in final `OV003`.
They allocate no additional storage. Modern source assignment does not prove
an original source filename or unique historical TU boundary.

All 22 prior emitted definitions, including 13 function symbols, retain their
full bytes and canonical relocation destinations. Only the proven row-field
aliases normalize to parent+4/+5. All 77 new data destinations match retail.
The two owned data ranges contain 1,167 object bytes and 89 linker-alignment
bytes. Actual-link evidence proves 59 providers over 1,159 public-address bytes;
whole-section checks also cover the eight-byte vtable preamble and alignment.

The first whole-TU attempt exposed the old tool model's missing linker
alignment rule. An unchanged native object with five-, seven- and eight-byte
strings links at offsets 0/5/12 under `ALIGNALL(1)`, and 0/8/16 under
`ALIGNALL(4)`. The generated OV003 block uses the latter. The separately
reviewed tool correction preserves the source and raw ELF inputs.

Final-config control, three-section scratch link and normal production pass:
106 modules and the 16 MiB ROM SHA-256
`d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`.
Strict function checks pass 11/11 with zero warnings. Nine baseline symbol
errors remain, with zero new errors. The optional raw-data diagnostic reports
the old `dCcAcPos_c` vtable and a new Title table false positive. Before the
per-TU rename map is applied, it resolves 46 local temporary names against
unrelated global names (184 differing bytes) and cannot resolve eight others
(32 blind bytes). Applying only the exact measured name map in a private
reproduction yields 432/432 verified table bytes with no blind words. The
actual prepared production object and complete linked table already pass.
This diagnostic defect is recorded as separate tooling continuation
`title-raw-local-resolution-001` on issue #4052, not suppressed or called an
unchanged result. Static checks and exact input hashes are recorded in the experiment; final immutable-range checks and
committed whitespace validation are recorded by producer queue evidence.

The earlier PR3937 candidate covered only 16 bytes, including only the first
pointer of this table. This work preserves current readable methods from
PR3955 and historical promotion PR2765. No v2 Title predecessor resource
record was found in the live queue; historical commits remain explicit inputs.

Six reconstruction findings remain open: scrolling-helper ownership, the OAM
call ABI, GX/G2 local contracts, raw rendering views, repeat-delay naming and
the volatile signed-character reader. Removing only that read volatility
emits 316 bytes instead of 320; its original reason remains unproven. The
inherited claim that the game boots into this scene was removed because
these consumers establish a level-selection implementation, not startup flow.
Cross-module globals remain outside this TU's assigned storage. No merge.
