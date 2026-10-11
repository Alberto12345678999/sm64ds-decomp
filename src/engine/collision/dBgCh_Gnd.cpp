//cpp
// Ground-ray collision query: a probe position (pos) swept downward against
// the KCL collider registry, reporting the floor through the dBgPi hit record
// the query embeds as its secondary base. pos is the search seed the
// colliders read back through GetClsnPos; mProbeHeight is the default ray
// length. DetectClsn at 0x02038f44 lives in its own TU in the query region.
//
// comment leftovers:
//   - func_020353b0 stays a free extern: the shared dBgCh-side bind helper is
//     owned by its own shard and called by the Lin/SphCrr query code as well.
#include "dBgCh_Gnd.h"

extern "C" {
void func_020353b0(char *c, int *p);    /* local extern: shared bind helper,
   writes the bound actor + its uniqueID into the query's dBgCh tail */
}

// @symbol _ZN9dBgCh_GndC1Ev
dBgCh_Gnd::dBgCh_Gnd() : mProbeHeight(0x1f4000) {}

// @symbol _ZN9dBgCh_GndD1Ev
// @symbol _ZN9dBgCh_GndD0Ev
// @symbol _ZThn16_N9dBgCh_GndD0Ev
// @symbol _ZThn16_N9dBgCh_GndD1Ev
dBgCh_Gnd::~dBgCh_Gnd()
{
}

// @symbol _ZN9dBgCh_Gnd10SetClsnPosERK7Vector3
void dBgCh_Gnd::SetClsnPos(const Vector3 &pos)
{
    this->pos = pos;
}

// @symbol _ZN9dBgCh_Gnd10GetClsnPosER7Vector3
void dBgCh_Gnd::GetClsnPos(Vector3 &res)
{
    res = pos;
}

/* Seed the probe and bind the owning actor -- the query's entry point. */
// @symbol _ZN9dBgCh_Gnd12SetObjAndPosERK7Vector3P8dActor_c
void dBgCh_Gnd::SetObjAndPos(const Vector3 &pos, dActor_c *actor)
{
    SetClsnPos(pos);
    func_020353b0((char *)this, (int *)actor);
}

// @symbol func_02037464
/* Absorbed from the retired arm9 helper func_02037464
 * (arm9 0x02037464..0x0203748c): reset the embedded dBgPi hit record, then
 * flag "no floor" (0x80000000) and clear the hit byte. Defined last because
 * this file emits .text in reverse source order, so the lead body lands at
 * the run's left edge. The Reset call is spelled as the member it is
 * (dBgPi.h arrives via dBgCh_Gnd.h). */
extern "C" void func_02037464(char *c)
{
    ((dBgPi *)(c + 0x10))->Reset();
    *(unsigned int *)(c + 0x44) = 0x80000000;
    *(unsigned char *)(c + 0x48) = 0;
}
