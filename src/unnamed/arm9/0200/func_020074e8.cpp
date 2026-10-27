//cpp
#include "types.h"
#include "math/Approach.h"

extern "C" {

/* The field used here, named as in include/dCamera_c.h. */
struct dCamera_c {
    char pad_000[0xb0];
    Vector3 savedLookAt; /* 0x0b0 */
};

int func_020074e8(struct dCamera_c *o) {
    ApproachLinear(o->savedLookAt.z, -0x28000, 0x2000);
    o->savedLookAt.x = -0x5000;
    return 1;
}
}
