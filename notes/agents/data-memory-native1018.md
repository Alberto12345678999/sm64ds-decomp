# Memory Match native state data

Task `data-memory-native1018`, [issue 4083](https://github.com/tangosdev/sm64ds-decomp/issues/4083).
Producer `codex-memory-native1018`; reviewed tool/source base
`d8e9946bc1f40ece143f28a8dac040f66c40b4fc`. The queue records the immutable
candidate and independent acceptance separately. No merge is authorized.

The compiled Memory Match TU now defines all 648 initialized data bytes at
ov006 `[0x0213cfc0, 0x0213d248)`: 25 eight-byte native member-pointer
constants, the eight-byte `g_profile_MG_MEMORY`, its own RTTI/name/full
152-byte vtable and seven card tables. Existing `.text`,
796-byte initializer, constructor-table word and 260-byte BSS ownership
remain intact. These are compiler definitions consumed by the complete TU
link, not data copied into C++ as ROM words.

The five runtime tables contain five scene, six round, four result, seven
card and three player handlers. Card and player handlers take an `int`;
scene, round and result handlers take no argument. Their native pointers
use those signatures without casts. `RoundWaitDeal` now returns `void`,
matching the round dispatch contract; its entire emitted body is unchanged.
The previous unused pointer value in r0 does not prove a historical return
type. This remains an inferred interface, not recovered original source.

The profile uses `BaseSpawnInfo<dScMgMemory_c>` with the typed factory and
behavior/render priorities `0x16a`. The factory retains its explicit
allocation, base construction, vptr transitions and embedded object calls;
the final pointer cast does not change its bytes. There are no other factory
declarations in the source/header population. The shared profile definition
is included; no catch-all header or rename ledger is changed.

The three coordinate arrays contain twelve interleaved `u16` x/y pairs for
easy, normal and hard difficulty. `CardMove` reads those pairs directly;
the tested `{u16 x, y}` form changes its emitted body, so the flat array
indexing remains a measured compiler constraint. The sprite table contains
seven card values times five flip frames, or 35 halfwords, followed by two
natural alignment bytes before the vtable. The six stored timing values are
`{8, 6, 4, 6, 24, 24}`. Consumers use indices 0 through 4; the sixth value's
historical purpose is unknown. The language table uses five runtime asset
handles resolved against the ROM's own catalog, preserving the existing
shared `int[]` declaration. These descriptive coordinate names are inferred
from consumers, not original identifiers.

The existing descriptive PMF identities remain the configuration labels.
The compiler's 25 local temporary names are mapped to them using the exact
handler destination and zero this adjustment. The complete native/canonical
map is in the experiment record and manifest. Their native local bindings
are preserved. Existing initializer and constructor-word global bindings
remain compatibility with configured identities; the old rationale that
DSD could not encode local symbols was false and is corrected here.

## Evidence and remaining work

The pinned compiler probe preserves all 69 prior definitions, including 49
emitted functions and 217 relocation sites, after the exact temporary-name
mapping. The initializer remains 796 bytes with all 32 relocation sites
unchanged. All 36 owned objects, 646 object bytes, two alignment bytes and
69 data relocation destinations match the retail overlay. The full vtable
has 152 bytes of storage; its public symbol begins eight bytes into that
storage and exposes 144 bytes. Raw baseline SHA256 is
`1a142e64df4a6410c7b6ca2dd82c992c69e649aad1d22c53d893d9be0c1b785a`;
candidate SHA256 is
`e14f33baa2806143c760de05ea81909f7cbc9de972d6e40157b1e4a1e93dbf15`.

The first expanded scratch run correctly rejected 15 vtable relocation
licenses that named only ov004, where the unchanged DSD configuration names
an explicit set of possible overlays. The corrected manifest retains each
exact configured set, and the raw proof checks both set equality and the
actual named destination's membership. This was a manifest census error;
neither source bytes nor guards changed. The rejected report is preserved.

Standalone verification reports 47/47 text matches and clean relocation
destinations, while refusing its existing initializer classification as one
unlicensed text symbol. That is a limitation, not a wholly passing standalone
promotion verdict. Complete initializer and TU linkage are checked separately.
Final production verifies all 42 requested source providers (36 initialized
data objects and six BSS objects), all 106 modules and the full retail ROM
SHA256 `d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`.
All 648 bytes come from the compiled TU. The full vtable prefix, initializer
and constructor word are checked against linked overlay bytes as well. Strict
verification reports 48/48 verified with no warnings or blocking errors. The
optional raw-data diagnostic retains its existing dCcAcPos vtable difference;
it is recorded separately rather than described as wholly green. The
experiment and queue receipt bind the exact inputs and immutable candidate.

The header's only consumer is this TU. The offset checker reads all 25
commented fields, reports no mismatch or unparsed field and reaches `0x5340`.
The source-coverage check adds exactly 648 source-built bytes with zero bytes
returned to ROM storage. Address attribution and existing ledger chains are
unchanged.

This is partial class reconstruction despite completing this initialized data
group. Memory2's first descriptor starts at
`0x0213d248`; the old `0x0213d288` boundary mistakenly included its first
eight descriptors. The current claim ends before those bytes. Raw card
walks, histogram addressing, `CheckFinished` aliasing, the handwritten factory,
unknown fields and shared declaration debts remain. The original source-file
grouping and descriptive method names are not uniquely recoverable.

Accepted predecessors are `mgread-memory-1007`, `asset-readability1014`,
`tools-raw-data-locals1017` and `tools-linker-align1017`. All inherited findings
are retained, including tool findings whose scope is historical and unchanged.
The cancelled `pr2877-interface-repair-0921` is historical context, not an
accepted ancestor. The temporary ov006 configuration reservation held by
`gate4047-main1018` was respected; this producer claimed only after it reached
DONE and a fresh exact-file/range check passed. The initial 208-byte candidate
passed its complete five-section scratch link and full matching ROM; that
proof is preserved separately. Before extending to all 648 bytes, the producer
released its lease, atomically added the remaining 440-byte reservation and
reclaimed the task. Final controls are regenerated for the expanded inputs.
PR3937 at inspected head
`96a5819fb0c939045f2e9707c4811c7d0d2a4ba2` proposes other ov006 changes,
not this source or initialized data interval. Its changing history is not ownership
authorization, and that PR was not edited.
