#include "types.h"
#include "nitro/fx/fx.h"

/* The 0x24-byte mass point func_ov007_020c844c allocates over a position
 * (func_ov007_020c83fc resets it). func_ov007_020c5a6c and
 * func_ov007_020c6e68 name its first slot Point::pos; the rest are named
 * from the integrators: func_ov007_020c81a0 (x/y) and this file (z) add
 * force to vel and vel to *pos, then clear force, which
 * func_ov007_020c7b2c's spring step accumulates. */
typedef struct Ov007Point {
    Vector3 *pos;   /* 0x00 */
    Vector3 vel;    /* 0x04 */
    Vector3 force;  /* 0x10 */
    s16 invMass;    /* 0x1c: Q12; func_ov007_020c844c stores the reciprocal
                     * of its mass argument (0x1000 = unit mass) */
    char pad_1e[2];
    s32 flags;      /* 0x20: bit 0 skips the integration */
} Ov007Point;

typedef char Ov007Point_size_must_be_0x24[sizeof(Ov007Point) == 0x24 ? 1 : -1];

/* One damped Euler step on the z axis: a is the damping factor, s the
 * step shift. */
void func_ov007_020c80c8(char *o, int a, int s)
{
    Ov007Point *pt = (Ov007Point *)o;
    if (!(pt->flags & 1)) {
        if (pt->invMass == 0x1000) {
            pt->vel.z += (pt->force.z - FX_MUL(a, pt->vel.z)) >> s;
        } else {
            pt->force.z -= FX_MUL(a, pt->vel.z);
            pt->vel.z += FX_MUL(pt->force.z, (pt->invMass >> s));
        }
        pt->pos->z += pt->vel.z >> s;
    }
    pt->force.z = 0;
}
