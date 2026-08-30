//cpp
// @symbol _ZN16daObjWaterfall_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method */
#include "daObjWaterfall_c.h"
extern signed char data_0209f2f8;

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
