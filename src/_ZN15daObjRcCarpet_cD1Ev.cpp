//cpp
// @symbol _ZN15daObjRcCarpet_cD1Ev
/* D1, the complete-object destructor. daObjRcCarpet_c's destructor is inline
 * so the genuine class TU can emit its retail D1/D0 pair without a D2. This
 * explicit call forces the standalone legacy object to emit D1 as well;
 * objisolate drops this forcing function and keeps only the bound destructor.
 * See notes/dtor-migration.md section 3. */
#include "daObjRcCarpet_c.h"

void _force_daObjRcCarpet_cD1(daObjRcCarpet_c *actor)
{
    actor->~daObjRcCarpet_c();
}
