//cpp
// @symbol _ZN10daSldMng_cD0Ev
/* A delete expression forces the compiler-spelled deleting destructor. */
#include "daSldMng_c.h"

void daSldMng_c_EmitDeletingDestructor(daSldMng_c *manager)
{
    delete manager;
}
