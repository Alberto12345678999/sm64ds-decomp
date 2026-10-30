//cpp
/* Ground-ray collision query: a probe position (pos) swept downward against
 * the KCL collider registry, reporting the floor through the dBgPi hit record
 * the query embeds as its secondary base. pos is the search seed the
 * colliders read back through GetClsnPos; mProbeHeight is the default ray
 * length. DetectClsn (0x02038f44) and DetectClsnSlot0 live in
 * d_bg_ch_sph_crr_query.cpp with the other registry scans. */
#include "dBgCh_Gnd.h"

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
    SetActor(actor);
}

// @symbol _ZN9dBgCh_Gnd11ResetResultEv
/* Hit-record reset at the run's left edge (reverse emission lands the last
 * definition lowest): clears the embedded dBgPi hit, flags "no floor"
 * (0x80000000) and clears the hit byte. */
void dBgCh_Gnd::ResetResult() {
    dBgPi::Reset();
    clsnY = 0x80000000;
    hasClsn = 0;
}
