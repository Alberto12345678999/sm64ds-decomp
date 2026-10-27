# Collision query readability, 2026-10-27

Local worktree: `C:/tmp/sm64ds-collision-readability1027`, branch
`cpp/collision-readability1027`, starting at
`69a9d665276e996f91f209b9032024a2c4bb9ef1`.

This is an ongoing folder-wide cleanup. The method names below are inferred
from implementation and callers, not recovered Nintendo function spellings.
The class identities already have ROM RTTI evidence in their headers.

## Named interfaces and evidence

| Address | Interface | Evidence |
| --- | --- | --- |
| arm9 020354b0 | `dBgCh::IsDetectingOrdinary` | Filter's fallback accepts ordinary surfaces only when mask 1 is set. |
| arm9 0203547c | `dBgCh::IsDetectingWater` | Filter checks mask 2 for CLPS water bit 5. |
| arm9 0203543c | `dBgCh::IsDetectingToxic` | Filter checks mask 8 for CLPS toxic bit 25; Player uses that surface predicate to update its toxic height. |
| arm9 02035468 | `dBgCh::EnableCameraMode` | Camera query initializer 0200897c always sets mask 4 after updating vanish behavior. |
| arm9 0203545c | `dBgCh::IsCameraMode` | The filter uses mask 4 to reject CLPS bit 24 and accept bit 26. |
| arm9 02037e2c | `CLPS::IsCameraPassThrough` | Paired camera-mode filter branch rejects these surfaces. |
| arm9 02037e14 | `CLPS::IsCameraOnly` | Paired branch rejects these surfaces when camera mode is absent. |
| arm9 02037464 | `dBgCh_Gnd::ResetResult` | Both ground registry scans reset the hit record, height sentinel, and hit byte before visiting colliders. |
| arm9 02037608 | `dBgCh_Lin::ResetResult` | Line setup restores the full endpoint/distance and clears the previous polygon hit. |
| arm9 02037b5c | `dBgCh_SphCrr::ResetQuery` | Sphere setup and actor reset clear displacement, flags, hit slots, and floor normal. |
| arm9 02037940 | `dBgCh_SphCrr::SetQueryFlags` | Moving/scaled mesh scans copy flags to their local sphere while clearing the floor/wall/under contact bits 0x1c. |
| ov002 020fea68 | `dM3dGLin::GetStart` | Copies the three words at line offset 0 into the caller result. |
| ov002 020fea4c | `dM3dGLin::GetEnd` | Copies the three words at line offset 0xc into the caller result. |

The flag predicates retain integer mask returns. Normalizing them to `bool`
would be a separate ABI/code-generation change. Both endpoint getters return
`Vector3`: mwccarm supplies the hidden result buffer in r0 and `this` in r1.
`lineEnd = GetEnd()` followed by `Vector3 startPoint = GetStart()` reproduces
the original local/temporary stack slots and call destinations exactly.

The camera setup caller now uses `dCamera_c`, `Player`, and `dBgCh` headers.
Two C camera callers explicitly pass the line query's zero-offset `dBgCh` base.
The retired hand-mangled caller exceptions are removed. Math calls use
`math/CalcLib.h`, and the root query's deallocator uses `Memory.h`.

## Shared-header effects

The two older Memory allocation declarations now omit parameter names, like
that header's remaining declarations. Named prototype parameters advance this
compiler's local-symbol counter even when they do not alter machine code.

Complete before/after objects were compared for 153 affected manifest-backed
consumers with compiler-local policies. The comparison checks allocated
section bytes, kind, flags, size, alignment, defined-symbol attributes/order,
and typed relocation destinations. Only `ov004/dScMgBase_c` requires current
compiler-local source mappings to move: five anonymous records shift by -2,
and `__arraydtor$323` becomes `__arraydtor$321`. Their configured retail
identities stay unchanged. Its 158 allocated sections and 658 relocations
compare equal after resolving local identities by section and offset.

Machine-readable comparison: `build/collision-memory-control/consumers.json`.
The temporary control headers retain the previous Memory declaration spellings;
no control source or header is enrolled in the production build.

## Validation

First checkpoint: 264/264 focused functions VERIFIED (23,840 bytes, no blind
relocations); full production build 106/106 exact modules, 11,380 reproduced
functions, intact-TU symbol/storage gates passing. Declaration agreement,
port references, dead references, language-mode ratchet and source style pass.
Reports are in this worktree under `build/collision-*.log` and
`build/collision-*.json`. The focused link check covers all directly changed
source files; the full production build covers shared-header consumers too.

## Remaining folder work

This change does not complete the folder-wide objective. Remaining work includes
`dBgCh_Actr` address-named accessors/workers, `dBgW` property accessors and callbacks,
mesh-coordinate transforms and KCL helpers, the CLPS water/toxic helpers and their
actor callers, sphere hit forwarders, and collision-list/clipper helpers.

The sphere hit forwarders currently preserve an `int` triangle ID while
`dBgPi::RecordHit` is declared with `s16`; resolve the interface from callers and
bytes before removing that bridge. Unknown virtuals and flags still need evidence.
No blanket extern removal or invented original names is justified by this pass.
