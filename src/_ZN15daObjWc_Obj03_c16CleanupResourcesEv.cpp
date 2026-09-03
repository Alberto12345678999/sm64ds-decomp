//cpp
// @symbol _ZN15daObjWc_Obj03_c16CleanupResourcesEv
/* daObjWc_Obj03_c::CleanupResources -- vtable slot 3. Releases the one shared file the class
 * holds; it never touches `this`, which is why the legacy C form could declare
 * itself nullary and still reproduce. */
#include "daObjWc_Obj03_c.h"
#include "SharedFilePtr.h"

extern SharedFilePtr data_ov029_02114270;

int daObjWc_Obj03_c::CleanupResources()
{
    data_ov029_02114270.Release();
    return 1;
}
