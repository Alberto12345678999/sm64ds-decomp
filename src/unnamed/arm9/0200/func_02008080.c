#include "types.h"

/* The fields used here, named as in include/dActor_c.h and include/dCamera_c.h. */
struct dActor_c {
    char pad_000[0x60];
    s32 mPosY; /* 0x060 */
};

struct dCamera_c {
    char pad_000[0x8c];
    Vector3 pos; /* 0x08c */
};

extern struct dActor_c *FindDemoActor(unsigned int ownerID);

int func_02008080(struct dCamera_c *cam) {
    struct dActor_c *a;
    int *dst;

    a = FindDemoActor(0x13);
    dst = &cam->pos.y;
    *dst = *dst + a->mPosY;
    return 1;
}
