//cpp
// @symbol _ZN24daPropeller_Heyho_Fire_c16CleanupResourcesEv
/* recovered: shared header, real C++ method
 *
 * Releases the 1 shared file(s) InitResources claimed.
 *
 * TOUCHES NO FIELD. The ROM body takes no `this`; as a method it now receives
 * one and ignores it, which measured byte-free.
 */
#include "daPropeller_Heyho_Fire_c.h"
#include "SharedFilePtr.h"

extern "C" {
extern int data_ov065_0211d610[];
}

int daPropeller_Heyho_Fire_c::CleanupResources()
{
    ((SharedFilePtr *)data_ov065_0211d610)->Release();
    return 1;
}
