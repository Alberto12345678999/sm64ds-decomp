# DSMT native metadata

Task `data-dsmt-native1018`, [issue4085](https://github.com/tangosdev/sm64ds-decomp/issues/4085).
Producer `codex-dsmt-native1018`; tested dependency base
`fe73dec6ed2f323d1d009f693d2e98c9c7c29280` from
[PR4073](https://github.com/tangosdev/sm64ds-decomp/pull/4073).
The queue records the immutable candidate and independent review separately.
No merge is authorized.

The existing DSMT translation unit now defines 184 initialized bytes in two
complete named sections: ov007 `[0x02103260,0x02103290)` and
`[0x021032a8,0x02103330)`. Eight native objects occupy 181 bytes; three
measured internal alignment bytes complete these ranges. The definitions are
the scene and nested callback RTTI/name/vtable objects, a typed
`BaseSpawnInfo<dScDSMT_c>` and the pending-music integer.

The callback vtable has 24 bytes of storage beginning at `0x021032a8`, with
16 public bytes beginning at `0x021032b0`. The scene vtable has 80 bytes of
storage beginning at `0x021032e0`, with 72 public bytes at `0x021032e8`.
Existing numeric public aliases remain identities within that same native
storage. No additional vtable object or raw integer callback array is added.
Native RTTI/name bindings and global vtable bindings are retained.

The profile points to a typed scene factory and has behavior/render priorities
1 and 3. The factory still performs its inherited explicit allocation, base
construction, vptr stores and fader construction. Only its return type and final
cast change; all emitted bytes and relocations remain identical. This is a
typed boundary, not a claim that the constructor has been recovered.

The pending-music scalar starts at -1. The setup helper stores a requested
music ID, and `Behavior` loads it after the delay then returns it to -1.
Its address-derived name is retained because the shared declaration is reserved.
Consumer roles do not establish original names or original TU boundaries.

## Proof and remaining work

The pinned raw comparison preserves all 34 prior definitions, including 20
functions and 209 relocations. All eight data objects and their 31 relocations
match retail, including exact configured allowed-module sets. Baseline raw
SHA256 is `acae5d94c226e963a1658881a00c10042a8e178140fb59aef72d5fc98fbe4101`;
candidate raw SHA256 is `fde2467972ba6133497c7f9bef4d1615150492fa0bed57e9bdee690378c91666`.
Standalone verification reports 20/20 matches, clean isolation and clean
relocation destinations. The complete scratch link and normal build verify all 106 modules and the
full ROM SHA256 `d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`.
All eight requested data providers come from this compiled TU. Separate final
overlay-byte, map and LCF checks prove both full vtables, both public aliases
and the excluded 24/16-byte gap providers. The nine baseline DSD strict-symbol
errors remain with zero new errors; that diagnostic is not wholly green.
The optional raw-data scanner retains its old dCcAcPos vtable difference.
The queue receipt records immutable commit binding and commit-scoped strict checks.

The middle `[0x02103290,0x021032a8)` interval contains six callbacks consumed
by the subsystem's interface installation. Its existing scalar `int`
declaration in `include/decl_common.h` conflicts with a readable native
callback aggregate. That header is reserved by `jump-contract-repair-0918`.
This table remains required follow-up; it is not hidden behind a fabricated
alias or copied address blob. The trailing 16 bytes at
`[0x02103330,0x02103340)` remain unknown and ROM-owned, not assumed padding.
Both excluded intervals have separate module sections and require final
gap-provider proof.

The unchanged source-coverage diagnostic reports net zero because it does not
count named initialized sections. That output is not evidence for the 184-byte
addition. Exact manifest ranges, native object extents and final linked provider
records establish the addition separately; the original text ownership remains
unchanged. A general diagnostic extension belongs in a separate tool change.

The class header remains byte-identical and its only source consumer is this
TU. Its callback comment about discarding vtable/RTTI passengers describes
function-only isolation; this whole-TU production path retains and owns both
classes' native metadata. Existing raw shared-layout access, the local save-record structure,
manual lifecycle and address-derived helpers remain partial reconstruction.
Historical text-only and old ROM-packaging diagnostics remain historical;
fresh controls establish the candidate's actual current result.

The original TU promotion landed in [PR3327](https://github.com/tangosdev/sm64ds-decomp/pull/3327).
Its cancelled queue task `tu-ov007-ov065-0928` is historical context, not an
accepted verifier handoff. Accepted predecessor tasks are
`native-destructor-repair-0922`, `pr3955-final-comment-review1017` and
`tools-data-section-routes1018`; all 30 inherited findings are retained.
Their unrelated historical scopes are not new source-completion claims.
The pre-edit source/header/manifest/symbol blobs equal inspected main
`06586a6aae3f05886f95a906d0c97f539993264c`; its differing delinks rows are
unrelated C-to-C++ path migrations and are not transplanted into this branch.

[PR3937](https://github.com/tangosdev/sm64ds-decomp/pull/3937), at inspected
head `96a5819fb0c939045f2e9707c4811c7d0d2a4ba2`, proposes a raw 16-byte
public callback-vtable definition. This native full-storage reconstruction
overlaps and would supersede that part; future integration must reconcile
the duplicate proposal. That PR was not edited or treated as accepted source.
