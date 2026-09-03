//cpp
#include "WaterDiamond.h"
#include "daObjWc_Mizu_c.h"

void WaterDiamond::SetWaterID()
{
  dActor_c *water;
  if (mWaterID != 0) return;
  water = 0;
  for (;;) {
    water = dActor_c::FindWithActorID(0x65, water);
    if (water == 0) goto done;
    if (mWaterParam == ((daObjWc_Mizu_c *)water)->mUseSpawnPosY) break;
  }
  mWaterID = water->uniqueID;
done:
  if (mWaterID != 0) return;
  MarkForDestruction();
}
