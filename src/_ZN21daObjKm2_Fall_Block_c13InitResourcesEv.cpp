//cpp
// @symbol _ZN21daObjKm2_Fall_Block_c13InitResourcesEv
/* recovered: real C++ method */
/* daObjKm2_Fall_Block_c::InitResources() -- forwards `this` and the class's shared parameter block to
 * the generic implementation the family shares. */
#include "daObjKm2_Fall_Block_c.h"


extern "C" {
int func_ov098_0213a794(void *self, void *data);
extern int data_ov045_021130ac[];
}

int daObjKm2_Fall_Block_c::InitResources()
{
    return func_ov098_0213a794(this, data_ov045_021130ac);
}
