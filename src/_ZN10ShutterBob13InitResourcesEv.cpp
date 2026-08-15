//cpp
// @symbol _ZN10ShutterBob13InitResourcesEv
/* recovered: named members + shared header, real C++ method
 *
 * The local `class Actor {}` and `class MeshColliderBase` shadows are gone:
 * ShutterBob now really derives from Platform through daObjSwdoor_c, so the
 * collider is Platform's own mMeshCollider and `this` is already an Actor.
 * The flat header's `u8 mMovingMeshCollider` marker at 0x124 was standing in
 * for exactly that member.
 */
#include "ShutterBob.h"

extern "C" {
extern int func_ov002_020bad10(void *c, void **f);
}
extern int data_ov014_021145c4;

int ShutterBob::InitResources()
{
    int r4 = func_ov002_020bad10(((char *)this), (void **)&data_ov014_021145c4);
    mMeshCollider.Enable(this);
    return r4;
}
