//cpp
// @symbol _ZN10daSldMng_cD1Ev
/* Force mwccarm to materialize daSldMng_c's inline complete destructor. */
#include "daSldMng_c.h"

void daSldMng_c_EmitDestructor(daSldMng_c *manager)
{
    manager->~daSldMng_c();
}
