#include "types.h"
#include "nitro/fx/fx.h"
/* AddVec3 still defines its vector as its own struct Vec3;
   declared as defined, the call casts. */
struct Vec3;
extern void AddVec3(struct Vec3 *a, struct Vec3 *b, struct Vec3 *c);

struct Inner { int f00; int f04; char pad[4]; int f0c; int f10; };
struct Mid { char pad[0xec]; int fec; char pad2[4]; void **ff4; };

extern void *data_ov007_0210342c;

void func_ov007_020b2454(Vector3 *out, Vector3 *r1) {
    int w;
    struct Mid *m;
    struct Inner *in;
    Vector3 *base;
    Vector3 b;
    Vector3 a;

    m = (struct Mid *)data_ov007_0210342c;
    in = (struct Inner *)((void **)*m->ff4)[3];
    a.z = 0;
    a.y = 0;
    a.x = 0;
    base = (Vector3 *)((char *)in + 0x24);
    /* fec is only ever 0 or 1 here; the ROM has no default arm either, so
       any other value would read w uninitialised. */
    switch (m->fec) {
    case 0:
        a.y = FX_MUL((-in->f10), 0x8543);
        w = 0xbb8;
        r1->x = r1->x - 0x5000;
        break;
    case 1:
        a.y = FX_MUL(in->f04, 0x987b);
        w = 0x960;
        r1->x = r1->x - 0xa000;
        break;
    }
    AddVec3((struct Vec3 *)base, (struct Vec3 *)&a, (struct Vec3 *)&b);
    out->x = base->x;
    out->y = (int)(((long long)(0x1000 - w) * b.y + (long long)w * base->y) >> 12);
}
