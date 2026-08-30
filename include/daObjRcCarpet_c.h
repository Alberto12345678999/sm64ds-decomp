#ifndef DAOBJRCCARPET_C_H
#define DAOBJRCCARPET_C_H

#include "types.h"

/* The flying carpet. Its factory is FlyingCarpet_Spawn, and its own C++ base is
 * PathLift (include/PathLift.h) -- RTTI's own class for that level is
 * `dPathLiftActor_c` (ov002:0x0210af0c), but every mangled symbol in the ROM
 * spells the base `PathLift` (_ZTV8PathLift, _ZN8PathLiftD1Ev, ...), so this
 * header follows PathLift.h and daObjPathLift_c.h's precedent (#1589) and uses
 * that name. daObjPathLift_c (ov100) is a direct sibling of this class under
 * the same intermediate.
 *
 *   _ZTI15daObjRcCarpet_c  ov036 0x02113f4c
 *   _ZTS15daObjRcCarpet_c  ov036 0x02113f64
 *   _ZTV15daObjRcCarpet_c  ov036 0x02113f9c  (its record sits at V-4)
 *   kind  __si_class_type_info, ONE base, subobject offset 0
 *   base  dPathLiftActor_c (= PathLift), ov002 0x0210af0c
 *
 * SIZE 0x4c0, the literal FlyingCarpet_Spawn (src/FlyingCarpet_Spawn.cpp) passes
 * to fBase_c::operator new. PathLift ends 0x450; the D1 destructor
 * (func_ov036_02112158, this class's own) destroys only a ModelAnim at 0x450
 * before storing PathLift's own vtable and running PathLift's inlined cleanup
 * (Model[3] array), so ModelAnim is this class's only member with a
 * constructor/destructor of its own -- matching the ONE call
 * (_ZN9ModelAnimD1Ev) the D1 relocations show, beyond the calls
 * include/daObjPathLift_c.h's own D1 already documents for PathLift's own
 * teardown (__destroy_arr, MovingMeshColliderD1Ev, ModelD1Ev, dActor_cD2Ev).
 *
 * PathLift owns the PathPtr at +0x430 and the tail fields at +0x428, +0x42c,
 * +0x43c and +0x440. Both PathLift descendants construct the PathPtr at the
 * same offset, and their methods use the same tail layout. PathLift.h names
 * these members so derived code no longer needs raw base-offset casts.
 *
 * unk_4bc, read/written only by this class's own Behavior/func_ov036_021122c0/
 * func_ov036_0211224c as a plain accumulator for _Z14ApproachLinearRiii, closes
 * the object exactly: 0x4bc + 4 = 0x4c0. The 8 bytes at 0x4b4..0x4bc are
 * unwitnessed by any reachable function and stay explicit padding.
 */

#ifdef __cplusplus

#include "PathLift.h"
#include "ModelAnim.h"

struct daObjRcCarpet_c : PathLift {
    ModelAnim mModelAnim;      /* 0x450 */
    u8  pad_4b4[0x8];
    s32 unk_4bc;                /* 0x4bc */

    /* Inline plus vtable instantiation is load-bearing: mwcc emits retail's
       D1 then D0 pair, with no homeless D2. PathLift's destructor is inline,
       so its member/base cleanup is folded into both derived variants exactly
       as the ROM spells it. InitResources anchors this TU's class group. */
    virtual ~daObjRcCarpet_c() {}

    int InitResources();
    int CleanupResources();
    int Behavior();
    int Render();
};

typedef char daObjRcCarpet_c_size_must_be_0x4c0[sizeof(daObjRcCarpet_c) == 0x4c0 ? 1 : -1];

#endif /* __cplusplus */

#endif /* DAOBJRCCARPET_C_H */
