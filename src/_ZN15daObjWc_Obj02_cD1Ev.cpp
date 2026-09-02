//cpp
// @symbol _ZN15daObjWc_Obj02_cD1Ev
/* The class-body destructor is real C++. This otherwise-unused explicit call
 * forces mwccarm to emit its out-of-line D1 copy; objisolate keeps that symbol
 * and discards the forcing wrapper. */
#include "daObjWc_Obj02_c.h"

void daObjWc_Obj02_c_EmitDestructor(daObjWc_Obj02_c *p)
{
    p->~daObjWc_Obj02_c();
}
