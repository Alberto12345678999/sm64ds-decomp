//cpp
// @symbol _ZN18daObjClockHuriko_c16CleanupResourcesEv
/* daObjClockHuriko_c::CleanupResources -- vtable slot 3, ov013 0x02111214.
 * Releases the one shared file the painting holds; it never touches `this`. */
#include "daObjClockHuriko_c.h"
#include "SharedFilePtr.h"

extern SharedFilePtr data_ov013_02112280;

s32 daObjClockHuriko_c::CleanupResources()
{
    data_ov013_02112280.Release();
    return 1;
}
