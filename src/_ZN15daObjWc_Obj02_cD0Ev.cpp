//cpp
// @symbol _ZN15daObjWc_Obj02_cD0Ev
/* A delete-expression forces mwccarm to emit the deleting destructor. The
 * inherited inline dActor_c::operator delete supplies the actor-heap release
 * used by the ROM. */
#include "daObjWc_Obj02_c.h"

void daObjWc_Obj02_c_EmitDeletingDestructor(daObjWc_Obj02_c *p)
{
    delete p;
}
