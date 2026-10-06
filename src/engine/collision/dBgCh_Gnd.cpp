//cpp
// @symbol _ZN9dBgCh_Gnd12SetObjAndPosERK7Vector3P8dActor_c
// @symbol _ZN9dBgCh_Gnd10GetClsnPosER7Vector3
// @symbol _ZN9dBgCh_Gnd10SetClsnPosERK7Vector3
// @symbol _ZN9dBgCh_GndD0Ev
// @symbol _ZN9dBgCh_GndD1Ev
// @symbol _ZN9dBgCh_GndC1Ev
// @symbol _ZThn16_N9dBgCh_GndD0Ev
// @symbol _ZThn16_N9dBgCh_GndD1Ev
/* dBgCh_Gnd -- the ground-ray collision query: a dBgCh plus a dBgPi hit
 * record at 0x10 (ROM RTTI _ZTS9dBgCh_Gnd @ 0x02099224, vtable
 * _ZTV9dBgCh_Gnd @ 0x02099264). pos is the probe position DetectClsn
 * seeds and the colliders read back through GetClsnPos.
 *
 * Deferred codegen emits the plain members in reverse definition order
 * and the lifecycle groups in their fixed order, so the file defines
 * ctor and dtor first. The dBgPi-base destructor thunks (_ZThn16_)
 * are compiler-emitted after C1. */
#include "dBgCh_Gnd.h"

extern "C" void func_020353b0(void *ray, void *actor);

dBgCh_Gnd::dBgCh_Gnd() : mProbeHeight(0x1f4000) {}

dBgCh_Gnd::~dBgCh_Gnd()
{
}

void dBgCh_Gnd::SetClsnPos(const Vector3 &pos)
{
    this->pos = pos;
}

void dBgCh_Gnd::GetClsnPos(Vector3 &res)
{
    res = pos;
}

void dBgCh_Gnd::SetObjAndPos(const Vector3 &pos_, dActor_c *actor_)
{
    SetClsnPos(pos_);
    func_020353b0(this, actor_);
}
