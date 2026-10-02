//cpp
#include "types.h"
// @symbol _ZN14daObjFl_Coin_c8BehaviorEv
#include "daObjFl_Coin_c.h"
// recovered name: daObjFl_Coin_c_Behavior
/* recovered: renamed to Class_Method */
/* daObjFl_Coin_c::Behavior - recovered from vtable slot identity */
extern "C" {
extern int _ZN8dActor_c13DistToCPlayerEv(void *self);
}

s32 daObjFl_Coin_c::Behavior() {
    char * a = (char *)this;
    switch (*(u8 *)(a + 0xd5)) {
    case 0:
        if (*(u8 *)(a + 0xd4) == 3) {
            if (_ZN8dActor_c13DistToCPlayerEv(a) < 0x3e8000) {
                (*(u8 *)(((int)a + 0xd5)))++;
            }
        }
        break;
    case 1:
        break;
    }
    return 1;
}
