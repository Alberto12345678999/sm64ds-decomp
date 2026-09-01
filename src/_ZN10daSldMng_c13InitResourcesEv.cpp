//cpp
// @symbol _ZN10daSldMng_c13InitResourcesEv
#include "daSldMng_c.h"

extern Vector3 data_ov019_021135d8;

int daSldMng_c::InitResources()
{
    mPosX = data_ov019_021135d8.x;
    mPosY = data_ov019_021135d8.y;
    mPosZ = data_ov019_021135d8.z;
    mKillTimer = 0x78;
    return 1;
}
