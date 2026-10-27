//cpp
#include "common.h"
#include "dActor_c.h"

extern "C" {

extern u32 data_0209b2a4[0x10]; /* 0x0209b2a4 */

dActor_c *func_0200e4e4(u32 param1) {
    u32 *slot = data_0209b2a4;
    s32 i = 0;
    for (;;) {
        if (*slot == 0) {
            dActor_c *a = dActor_c::Spawn(0x160, param1, *(const Vector3 *)0, 0, -1, -1);
            if (a)
                *slot = a->uniqueID;
            return a;
        }
        i++;
        slot++;
        if (i >= 0x10)
            break;
    }
    return 0;
}
}
