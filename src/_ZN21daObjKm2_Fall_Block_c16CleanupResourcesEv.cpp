//cpp
// @symbol _ZN21daObjKm2_Fall_Block_c16CleanupResourcesEv
/* recovered: real C++ method */
/* daObjKm2_Fall_Block_c::CleanupResources() -- forwards `this` and the class's shared parameter block to
 * the generic implementation the family shares. */
#include "daObjKm2_Fall_Block_c.h"


extern "C" {
int func_ov098_0213a2cc(void *self, void *data);
extern int data_ov045_021130ac[];
}

int daObjKm2_Fall_Block_c::CleanupResources()
{
    return func_ov098_0213a2cc(this, data_ov045_021130ac);
}
