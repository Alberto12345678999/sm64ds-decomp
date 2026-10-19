# Entry native metadata and sprite lists

This commit continues task `data-entry-metadata1018`, issue
[4084](https://github.com/tangosdev/sm64ds-decomp/issues/4084), from accepted tool
base `fe73dec6ed2f323d1d009f693d2e98c9c7c29280`. The active queue workflow is
`18af52b49b9fb5663d417bdfa86109b7b157aaa3`. Producer session
`codex-entry-expanded1018` uses branch `data/entry-metadata1018`. The queue records
the immutable output and independent review. Publication is authorized; merging
is not. The next owner independently reviews and verifies this exact commit.

## Native storage and evidence

The complete delinks for `src/game/stages/d_s_entry.cpp` now retain four ov075
data slices totaling 276 bytes: 271 native object bytes and five natural internal
alignment bytes. The default build compiles the intact source object and routes
its native sections; the enrolled ranges are not filled from the cartridge.

| Storage interval | Native objects |
| --- | --- |
| `0211c8e0..0211c954` | Three 12-byte RTTI records, the 13-byte Entry type name, three alignment bytes, three 16-byte sprite lists, and the 16-byte icon vtable storage. |
| `0211ca1c..0211ca4c` | The 22-byte icon type name, two alignment bytes, and 24-byte graph-callback vtable storage. |
| `0211cb44..0211cb64` | The 32-byte graph-callback type name. |
| `0211d2fc..0211d34c` | The 80-byte Entry vtable storage. |

All three vtables include their two-word ABI prefix. Their public address points
are eight bytes into storage and expose 8, 16 and 72 bytes respectively. The nine
ABI objects were already emitted by the key-function source; this change admits
them as native providers. Ten inherited ancestor metadata definitions retain
their separately configured canonical homes. Five unreferenced emitted functions
retain their existing dead-strip policy. No fabricated data alias is introduced.

The new lists at `0211c914`, `0211c924` and `0211c934` use the existing `OamAttr`
header: two entries of four unsigned 16-bit fields. Both sprites are drawn; the final
entry has `attr3 == 0xffff`, tested after drawing. Original variable names and
artwork roles remain unproven, so address-based names remain.

The first list is frame 4 of five at `0211cd7c`, reached from animation header
`0211ca74`, with duration 40. The other lists are frame 3 of six at `0211cfb4` and
`0211cfe4`, reached from headers `0211cc54` and `0211cc5c`, with duration 4.
Entry setup `021188b4` stores these headers in animation objects at scene offsets
`0x20c` and `0x238`. The frame walker `0202044c` selects an eight-byte pointer/time
pair and installs the sprite-list pointer; Entry render `021184b0` calls animation
render `0202048c`. Identity scale, zero rotation and mode 1 select the list-rendering
RenderSub path. The Matrix2x2 overload renders a single entry and is not evidence
for the sentinel loop. The independent consumer report is retained in the
experiment record with source/config hashes.

## Rejected layout and scope coordination

An earlier 225-byte metadata-only layout passed raw and routing helper checks but
failed the actual stock control: DSD aligned the 49-byte first slice to four bytes
before copying its separate three-byte gap. Later data moved and only 104 of 106
modules matched; no full ROM was accepted. This is an introduced failed trial,
not a baseline defect. The failed report and patch remain in private build state.
Adding the three actual adjacent sprite lists makes that alignment internal to
native storage. No fake padding array, weaker checker or linker workaround is used.

The producer released its first lease, atomically added `[0211c911,0211c944)` to
the reservation, and reclaimed before changing tracked source/config. Shared
headers and symbols remain unchanged. The original global data prefix and the
existing `d_ent_obj.cpp` claim are preserved. Intervening ranges stay outside
Entry ownership and their bytes are checked in the production link.

PR3937 at observed head `96a5819fb0c939045f2e9707c4811c7d0d2a4ba2`
edits seven other ov075 data/BSS ranges with no overlap here. It still shares the
delink file, requiring explicit reconciliation and fresh composition proof before
landing. Neither that PR nor the protected primary checkout is modified.

## Proof and remaining work

The pinned 2004/b56 raw baseline is 13,640 bytes, SHA-256
`ac615f91f7b8bfe3a848e978f129f4268976c34f4ca1da41635f5b32cc053869`.
The final candidate object SHA-256 is
`a41f6d890379094ac52def3dee85e095dcdef9fbad790bf1789bd6f0903f3c44`.
All 39 prior definitions, 20 emitted functions and 137 prior relocations remain
identical. The three new lists are the only new definitions. All 36 native data
relocations match configured destinations and exact allowed module sets, including
the `overlays(0,1)` ancestor home. The 15 enrolled functions pass strict relocation
checks with zero blind warnings. Static style, declaration agreement, conflicts,
source coverage and port-reference gates pass; no shared header is changed.

Expanded stock control, TU scratch and default production each reproduce all 106
modules and the full 16 MiB ROM, SHA-256
`d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`.
Nine baseline DSD symbol diagnostics remain; they are not a clean symbol check.
The production audit verifies 12 compiler providers, all full vtable storage,
the alignment bytes, intervening ranges and hashed inputs/artifacts. A fresh
clean-commit provider run and committed-blob checks precede the immutable offer;
that later evidence is recorded separately rather than embedding this commit's
own SHA. Independent verification and private PR validation remain separate gates.

The old text-only verification snapshot is retained under
`historical_text_verification`. Restoring that snapshot as the active record
initially caused normal admission to reject its legacy string-valued linkcheck.
The current verification dictionary is generated from the actual successful
expanded scratch report. No build-tool guard was changed.

This is partial reconstruction, not a completed Entry TU. The lower source owns
15 text functions; 58 loose helpers and upper methods, factories and initializer
remain split. Legacy `scene-tu-reduce-1002` ownership is retained. Fields, raw
interfaces, original names and wider class consolidation remain future work.
There are no source moves or renames; address-keyed author credit is unchanged.
All 29 inherited findings and six new findings survive in
`notes/experiments/data-entry-metadata1018.json`, including unrelated predecessor
continuations as historical lineage rather than a claim that this PR fixes them.
