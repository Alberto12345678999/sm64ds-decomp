# Entry native sprite lists and pointer tables

Task `data-entry-sprites1018`, [issue #4084](https://github.com/tangosdev/sm64ds-decomp/issues/4084), tested base `80540cd731544149a70ba014b177a7cd7c79fce6`. This is a partial continuation of accepted `data-entry-metadata1018` / merged [PR #4086](https://github.com/tangosdev/sm64ds-decomp/pull/4086). It reconstructs 596 additional initialized bytes in the existing Entry source slice; it does not complete the split historical scene TU.

The new definitions use the existing `OamAttr` type: four unsigned 16-bit attribute words per 8-byte entry. OAM rendering draws each entry, then stops when `attr3 == 0xffff`. Seventeen lists therefore have measured native extents totaling 544 bytes. Two native `OamAttr*` tables add 52 bytes and 13 exact relocations. No synthetic padding or byte-blob object is added. Numeric artwork identities are retained where exact original roles and identifiers remain unproven.

| Native group | Addresses | Bytes |
| --- | --- | ---: |
| Eight one-entry templates | `0211c6f0`, `0211c708`, `0211c720`, `0211c730`, `0211c778`, `0211c7c0`, `0211c870`, `0211c890` |64|
| Four four-entry templates | `0211cac4`, `0211cae4`, `0211cb04`, `0211cb24` |128|
| One eight-entry template | `0211d084` |64|
| Four nine-entry templates | `0211d144`, `0211d18c`, `0211d1d4`, `0211d21c` |288|
| Five-pointer selected-character table | `0211c954..0211c968` |20|
| Eight-pointer choice table | `0211cb64..0211cb84` |32|

`icon_c::Render` consumes the two arrows directly and selects the two pointer tables. `func_ov075_02118f38` creates four type 7 icons with indices 0..3, and rendering may add 4 for the alternate presentation. It creates the type 13 selected-character icon with initial selection 4; the local touch-selection loop chooses 0..3. The player-row renderer `func_ov075_0211621c` consumes two more one-entry templates. The remaining template addresses are reached through the two source-owned tables. These consumers and the OAM sentinel loop support the types/extents independently of inventory windows.

The inventory's28-byte window at `0211cb64` ended at an interior label and was not a seven-element array. `data_ov075_0211cb80` names its eighth pointer. `data_ov075_0211d1ac` and `data_ov075_0211d1c8` name byte offsets 32 and 60 within the 72-byte list at `0211d18c`. All three identities remain configured and must survive as zero-storage linked aliases; none becomes another compiler object.

Fourteen complete named data routes cover 872 initialized bytes: the accepted 276-byte metadata/sprite scope plus 596 new object bytes. Module sections are partitioned only at actual native boundaries; existing `d_ent_obj.cpp` ownership and every intervening ROM gap remain separate. The source remains the existing 15-function partial Entry TU. Its header, `OamAnimation.h`, `OamAttr.h`, ancestor headers, the separate upper methods/initializer, and attribution ledgers are unchanged. The active `scene-tu-reduce-1002` reservation for the separate BeforeInitResources leaf and ancestor headers remains respected.

The four observed bytes at `0211c6e8` stay ROM-owned. The index expression alone does not prove whether the trailingzero is a fourth value or alignment. Other helpers, lifecycle/PMF/BSS reconstruction and artwork naming remain explicitly unfinished.

Fresh queue and fully paginated open-PR audits are preserved in the private plan. Open PR #3937 and PR #4096 touch the same module configuration but propose disjoint ranges. Their future integration still needs explicit configuration reconciliation; neither proposal was edited. PR #4086 is already merged into this base.

The five inherited deadstrip-function policies retain their exact behavior. Their current explanations are corrected to measured unconfigured/emitted/unreferenced variants; missing configured identities do not prove those functions never existed in the retail program. Original policy wording is retained in the experiment evidence.

Producer gates pass. The native probe preserves 42 prior definitions, 20 emitted functions and 137 relocations exactly; 15 strict functions pass with zero warnings. Full control and scratch checks reproduce all 106 modules and the 16 MiB ROM with SHA256 `d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`. The nine pre-existing strict-symbol diagnostics remain, with zero new errors; that diagnostic is not green.

The default normal build verifies 31 actual providers, all 381 current data claims, 247 BSS claims and 11,334 functions. The final checker proves 872 initialized bytes, all 49 prepared nontext relocations with complete configured module alternatives, native RTTI bindings, full 16/24/80-byte vtable storage versus 8/16/72-byte public extents, all three zero-size GLOBAL/NOTYPE aliases, continuous 2,808-byte text and exclusive named-data providers. The four excluded layout bytes remain a DSD gap. All 7,172 bound inputs/artifacts are rehashed. Named map rows omit compiler-vtable prefixes and alignment; their full storage is proved by actual prepared section contributions and linked module bytes, not fabricated map records.

Coverage reports +596 bytes with no loss. Declaration agreement, pinned style, manifest conflict, rename, reference and port checks pass. The optional broad raw-data scanner retains the existing dCcAcPos vtable diagnostic from two legacy destructor objects; it is distinct from the passing actual-provider/full-ROM result.

One comment was narrowed from an inferred no-character meaning to observed initial selection 4. Its earlier runtime artifacts are preserved separately; the final normal run and strict check bind the corrected source. Only documentation is finalized afterward, and exact committed input blobs are audited before offer. Independent acceptance remains required; no full original-TU completion is claimed. All 35 predecessor findings and five current findings are retained in the experiment.
