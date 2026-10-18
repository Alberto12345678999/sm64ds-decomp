# CapIcon native metadata ownership

This commit enrolls the unchanged class source's existing RTTI, type name and full vtable in the normal production link. It is a partial reconstruction, not a claim that every historical TU global is recovered.

Task `data-capicon-native1018`, issue [4101](https://github.com/tangosdev/sm64ds-decomp/issues/4101), producer `codex-capicon-native1018`, branch `data/capicon-data1018`. Source/tested base is `53300e62058b1a3f18e0af75c3e0e1251106af69`; queue workflow is `18af52b49b9fb5663d417bdfa86109b7b157aaa3`. The queue records this commit's immutable SHA. Independent review and PR validation remain subsequent gates; no merge is authorized.

## Scope and identities

The existing `src/ui/hud/d_cap_icon.cpp` and `include/CapIcon.h` are unchanged, as are all symbols and attribution. Only the complete delink entry and TU manifest change, with this handoff and the experiment report. Existing text remains OV001 `[020ab110,020ab41c)`. New data is `[020ad450,020ad478)`, 40 bytes:

- Native `_ZTI10dCapIcon_c`: 8 bytes at `020ad450`, native `STB_LOPROC`.
- Native `_ZTS10dCapIcon_c`: 13 bytes at `020ad458`, the `10dCapIcon_c` type-name string plus NUL, native `STB_LOPROC`.
- Three internal natural linker-alignment zero bytes at `020ad465..020ad468`.
- Native `_ZTV10dCapIcon_c`: full 16-byte storage at `020ad468`, `STB_GLOBAL`. Its public address `020ad470` describes two dispatch slots, 8 bytes. The first two storage words are zero and own RTTI; slots are D1 at `020ab3a0` and D0 at `020ab374`.

These are compiler ABI identities, not proposed historical identifiers. Numeric `data_ov001_020ad470` remains a public-address alias with zero additional storage. All five data relocations are licensed by their exact configured modules and destinations. The RTTI first word has raw `_ZTVN3abi17__class_type_infoE` addend 8. Storage-prefix address `0209a76c` plus 8 explains the retail pointer `0209a774`. The actual prepared object retains the public `_ZTVN3abi17__class_type_infoE` symbol with normalized addend 0; it does not import `data_0209a76c`. Both calculations resolve to the same retail pointer.

There is no initializer or ctor entry here. Only unconfigured C2/D2 compiler function variants remain deadstripped. No synthetic metadata objects, byte arrays, bindings or source rewrites were introduced.

## Limits and lineage

Adjacent dThIcon metadata begins `020ad478` and remains outside ownership. ARM9 `data_0209f3e8` slot storage and shared OV001 CapIconMgr/state BSS from `020ad620` remain excluded. Loop counts alone do not prove those shared arrays' extents. The existing plurality-based slot declaration, raw unique-ID access, encoded helper/field names and positional codegen pragmas remain reconstruction constraints, not newly recovered type evidence.

The class source already incorporates PR2782/2826 and later helper absorption/path moves. Live queue and complete open-PR file audits found no overlapping CapIcon leaf/range ownership before the successful producer claim. Predecessors are the accepted initialized-interior, initialized-start-alias and linker-alignment tools. Both inherited fixed findings and all current partial-scope findings are retained in `notes/experiments/data-capicon-native1018.json`; none is silently dropped.

## Validation

Producer normal production/provider proof passes. Fresh pinned source compilation exactly reproduces the base object SHA `8612001959a343fcebc1f4cc1a76e362ba00fddf1844c7a0843bf0b68d50467d`: all 12 emitted definitions, 9 emitted functions and 31 ELF relocations are unchanged. Seven licensed functions pass standalone and explicit strict checks; the two other emitted functions are the unconfigured C2/D2 variants. Complete retail data proof covers 37 native bytes, 3 internal alignment bytes and 5 data destinations. Historical standalone records are archived privately rather than presented as current ownership evidence.

Private artifacts are under `build/` in `C:/tmp/sm64ds-capicon-data1018`; ROM/compiler inputs and receipts are not committed. A subsequent verifier must rebuild this exact commit on the pinned base and establish actual final providers, public alias module/address, full storage bytes and complete ROM equality. The task remains partial while shared-data/source reconstruction findings are open.

The final-config source-independent control and candidate scratch link both reproduce all 106 modules and the full 16 MiB ROM, SHA256 `d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`. The scratch verifies both complete owned ranges. All nine existing strict-symbol diagnostics remain, with zero new; this is not a green strict-symbol census.

The default normal build verifies all three requested actual source providers, all 369 current data claims, 247 BSS claims and 11,334 functions. A separate final checker reads actual OV001 output bytes for the full 40-byte interval and full 16-byte vtable, verifies native RTTI/name bindings and the 8-byte public vtable, and locates `data_ov001_020ad470` as a zero-size GLOBAL identity in OV001. Adjacent dThIcon RTTI remains `_dsd_gap@ov001_2.o`. All 7,172 provider input/artifact hashes are rechecked. The normal measurement precedes the notes and commit only; final immutable evidence additionally compares bound tracked inputs to committed blobs. It does not reuse a source/config-mismatched run.

Commands: `python tools/tubuild.py verify ov001/dCapIcon_c`; `python tools/prepush_linkcheck.py --files src/ui/hud/d_cap_icon.cpp`; `python tools/tubuild.py linkcheck --baseline --module ov001 -j16`; `python tools/tubuild.py linkcheck ov001/dCapIcon_c -j16`; and `python tools/rombuild.py -j16 --report-json build/capicon-production.json --data-provenance-requests build/capicon-requests.json`. Normal/checker scripts and logs are preserved privately. Source style, declaration agreement, manifest conflicts, port references, rename ledger and dead-reference checks pass; coverage records +40 bytes and zero loss. No shared-header consumer expansion is needed because no header changed.

The optional broad raw-data diagnostic still reports the existing ARM9 `_ZTV10dCcAcPos_c` mismatch in two legacy destructor objects, two bytes per object. It is outside this scope and is separate from the passing actual-provider/module/ROM proof. Ten unrelated manifest serializations were restored only after parsed-JSON identity checks, before the final provider binding. The earlier discarded own-metadata receipts and private schema-trial errors are preserved as history, not current proof. Commit `a6b2f99bb2727be04844ae499469dbbd951e91f5` directly establishes the helper-absorption chronology cited in the manifest.

Independent review finding `capicon-prepared-relocation-rationale-001` corrected an overstatement in the preceding candidate: the raw storage-prefix calculation was incorrectly described as the prepared import. Direct inspection of the actual normal provider now proves public symbol plus zero. This follow-up changes only manifest rationale and evidence prose. Runtime results above belong to `f9fd54e4665411ceed3ede7791b702a0c4b4ad6a`; source, headers, delinks, symbols and every functional manifest field are identical, and re-preparing the same raw object under both manifests produces exactly the original prepared provider bytes and policy report. The old full input-binding record is retained under its original SHA rather than relabeled as a fresh run of this correction.
