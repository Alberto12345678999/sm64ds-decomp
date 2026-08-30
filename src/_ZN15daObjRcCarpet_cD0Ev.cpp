//cpp
// @symbol _ZN15daObjRcCarpet_cD0Ev
/* D0, the deleting destructor. There is no source expression that names D0,
 * but the vtable needs it. InitResources is daObjRcCarpet_c's first out-of-line
 * virtual/key function, so defining a disposable copy here makes mwcc emit the
 * vtable and its inline D1/D0 pair. objisolate keeps only the bound D0 and drops
 * the duplicate key function and data. See notes/dtor-migration.md section 3. */
#include "daObjRcCarpet_c.h"

int daObjRcCarpet_c::InitResources()
{
    return 0;
}
