//cpp
// @symbol _ZN15daObjWc_Obj07_c13InitResourcesEv
/* recovered: real C++ method */
/* daObjWc_Obj07_c::InitResources() -- forwards `this` and the class's shared parameter block to
 * the generic implementation the family shares. */
#include "daObjWc_Obj07_c.h"


extern "C" {
int func_ov002_020b676c(void *self, void *a, short arg2);
extern short data_ov029_02113fc4;
extern void *data_ov029_02113fd4;
}

int daObjWc_Obj07_c::InitResources()
{
    return func_ov002_020b676c(this, &data_ov029_02113fd4, data_ov029_02113fc4);
}
