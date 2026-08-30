//cpp
/* Manually curated shadow translation unit.
 * ov002/daObjWaterfall_c  (5 function(s))
 *
 * NOT ENROLLED and NOT CANONICAL.  The readable class and member definitions
 * are compiled only by tubuild's scratch pipeline while the five legacy
 * production sources remain authoritative.
 *
 * FUNCTION ORDER IS DELIBERATELY THE REVERSE OF THE ROM'S -- mwccarm 2004/b56
 * emits one .text section per function, in the REVERSE of source order, so
 * the highest-address ROM function is written FIRST here. Do not reorder;
 * see notes/tu-reconstruction-pilot-report.md sec 3 for the one documented
 * exception (a destructor's D0/D1/D2 group has compiler-chosen order).
 *
 * Assembled from these legacy one-function sources (ROM address order):
 *   [0] 0x020b6e08  src/_ZN16daObjWaterfall_cD1Ev.cpp
 *   [1] 0x020b6e2c  src/_ZN16daObjWaterfall_cD0Ev.cpp
 *   [2] 0x020b6e64  src/_ZN16daObjWaterfall_c8BehaviorEv.cpp
 *   [3] 0x020b6eac  src/_ZN16daObjWaterfall_c13InitResourcesEv.cpp
 *   [4] 0x020b6ee8  src/WaterfallMist_Spawn.cpp
 *
 * daObjWaterfall_c is the ROM-proven identity: the adjacent retail RTTI and
 * type-name records at 0x0210945c/0x02109468 spell it and point at this class's
 * vtable. The C ABI factory name remains WaterfallMist_Spawn because no ROM
 * evidence recovers its original source spelling.
 */

#include "daObjWaterfall_c.h"

extern "C" {
extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN8dActor_cC2Ev(void *);
extern void *_ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
    unsigned a, unsigned b, int x, int y, int z, const void *v, void *cb);
extern signed char data_0209f2f8;
}

struct daObjWaterfallSpawnInfo {
    daObjWaterfall_c *(*spawn)();
    s16 behaviorPriority;
    s16 renderPriority;
    u32 flags;
    Fix12i rangeOffsetY;
    Fix12i range;
    Fix12i drawDistance;
    u32 unk_18;
};

typedef char daObjWaterfallSpawnInfo_size_must_be_0x1c[
    sizeof(daObjWaterfallSpawnInfo) == 0x1c ? 1 : -1];

/* -------------------------------------------------------------------------- */
/* ROM ordinal 4 -- WaterfallMist_Spawn, 0x020b6ee8, size 0x30 */
/* -------------------------------------------------------------------------- */
// @symbol WaterfallMist_Spawn
extern "C" daObjWaterfall_c *WaterfallMist_Spawn(void)
{
    daObjWaterfall_c *p =
        (daObjWaterfall_c *)_ZN7fBase_cnwEj(sizeof(daObjWaterfall_c));
    if (p) {
        _ZN8dActor_cC2Ev(p);
        *(int *)p = (int)&_ZTV16daObjWaterfall_c[2];
    }
    return p;
}

/* 0x0210947c..0x02109498, immediately before vtable storage. */
extern "C" daObjWaterfallSpawnInfo WaterfallMist_SpawnInfo = {
    WaterfallMist_Spawn,
    0x00c5,
    0x0015,
    0x00800003,
    0x00060000,
    0x00300000,
    0x02000000,
    0
};

/* -------------------------------------------------------------------------- */
/* ROM ordinal 3 -- daObjWaterfall_c::InitResources, 0x020b6eac, size 0x3c */
/* -------------------------------------------------------------------------- */
// @symbol _ZN16daObjWaterfall_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method */
int daObjWaterfall_c::InitResources()
{
    signed char v;
    mParticleID = 0x24;
    v = data_0209f2f8;
    if (v != 0x16) {
        if (v == 0x21)
            mParticleID = 0xeb;
    } else {
        mParticleID = 0x71;
    }
    return 1;
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 2 -- daObjWaterfall_c::Behavior, 0x020b6e64, size 0x48 */
/* -------------------------------------------------------------------------- */
int daObjWaterfall_c::Behavior()
{
    mParticle = _ZN8Particle6System3NewEjj5Fix12IiES2_S2_PK11Vector3_16fPNS_8CallbackE(
        (u32)mParticle, mParticleID, mPosX, mPosY, mPosZ, 0, 0);
    return 1;
}

/* ROM ordinals 0/1 -- the compiler emits D1 and D0 from this definition. */
daObjWaterfall_c::~daObjWaterfall_c()
{
}
