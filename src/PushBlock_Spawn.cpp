//cpp
// @symbol PushBlock_Spawn
#include "daObjPushblock_c.h"

/* A natural `new daObjPushblock_c` emits the exact instruction bytes, but its
 * allocation relocation names global `_Znwm`; retail calls fBase_c's actor-
 * heap allocator at 0x02043444. CodeWarrior b56 rejects the placement-new
 * declaration needed to separate allocation from construction, so this real
 * C ABI factory keeps only that measured allocation/base/member seam explicit. */
extern "C" {
void *_ZN7fBase_cnwEj(unsigned int size);
void _ZN10dBgActor_cC2Ev(void *self);
void _ZN10dBgCh_ActrC1Ev(void *self);
}

extern "C" daObjPushblock_c *PushBlock_Spawn()
{
    daObjPushblock_c *actor =
        (daObjPushblock_c *)_ZN7fBase_cnwEj(sizeof(daObjPushblock_c));
    if (actor) {
        _ZN10dBgActor_cC2Ev(actor);
        *(void ***)actor = _ZTV16daObjPushblock_c;
        _ZN10dBgCh_ActrC1Ev(&actor->mWithMeshClsn);
    }
    return actor;
}
