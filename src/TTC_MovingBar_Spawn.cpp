//cpp
#include "daObjCtMecha05_c.h"

/* TTC_MovingBar_Spawn is the cartridge's proven C ABI spelling even though
 * the object it constructs is daObjCtMecha05_c. Natural `new` selects the
 * unresolved global allocator, so this boundary keeps retail's actor
 * allocator and measured base/member construction sequence explicitly. */
extern "C" {
extern void *_ZN7fBase_cnwEj(u32 size);
extern void _ZN10dBgActor_cC2Ev(dBgActor_c *actor);
extern void _ZN11ShadowModelC1Ev(ShadowModel *shadow);
extern int _ZTV16daObjCtMecha05_c[];

daObjCtMecha05_c *TTC_MovingBar_Spawn()
{
    daObjCtMecha05_c *actor =
        (daObjCtMecha05_c *)_ZN7fBase_cnwEj(sizeof(daObjCtMecha05_c));
    if (actor) {
        _ZN10dBgActor_cC2Ev(actor);
        /* This separately compiled factory imports the configured public
         * address point, so retail's store has addend 0. */
        *(int *)actor = (int)_ZTV16daObjCtMecha05_c;
        _ZN11ShadowModelC1Ev(&actor->mShadowModel);
    }
    return actor;
}
}
