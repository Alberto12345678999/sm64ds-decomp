#include "types.h"
#include "nitro/fx/fx.h"
/* func_0200814c at 0x0200814c
 *
 * Matched byte-for-byte with mwccarm 2004/b56 (arm9 main).
 */

/* The fields used here, named as in include/dActor_c.h and include/dCamera_c.h. */
struct dActor_c {
    char pad_000[0x5c];
    Vector3 mPos; /* 0x05c */
    char pad_068[0x8e - 0x68];
    short mAngleY; /* 0x08e */
};

struct dCamera_c {
    char pad_000[0x80];
    Vector3 lookAt; /* 0x080 */
    Vector3 pos;    /* 0x08c */
};

extern struct dActor_c *FindScriptPlayer(unsigned int arg0);
extern void Vec3_RotateYAndTranslate(Vector3 *out, const Vector3 *trans, short ang,
                                     const Vector3 *add);

int func_0200814c(struct dCamera_c *self) {
    struct dActor_c *a;
    int diff, absdiff, val;
    Vector3 v;

    a = FindScriptPlayer(0);
    diff = a->mPos.y - self->pos.y;
    v.x = 0;
    v.y = 0x50000;
    v.z = diff;
    absdiff = diff < 0 ? -diff : diff;
    val = FX_MUL(absdiff, -0x199);
    v.z = val;
    if (val > -0x64000)
        v.z = -0x64000;
    if (diff > -0x300000)
        Vec3_RotateYAndTranslate(&self->lookAt, &a->mPos, a->mAngleY, &v);
    return 1;
}