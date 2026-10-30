#include "types.h"
#include "nitro/fx/fx.h"
#include "Ov007Spring.h"

/* func_ov007_020c7560's mode 3: a damped spring along z only. The z offset
 * of from - to past dir.z, times stiffness (Q12), pulls it back toward
 * dir.z: from gets -stiffness * (offset - dir.z) and to the opposite. Each
 * end is damped by its own z velocity times damping. */
void func_ov007_020c7a84(Ov007Link *link, int stiffness, int damping) {
    Ov007Follower *a = link->from;
    int t = a->target->z - link->to->target->z - link->dir.z;
    int m1 = FX_MUL(stiffness, t);
    int m2 = FX_MUL(damping, a->velocity.z);
    int nm1 = -m1;
    a->force.z += nm1 - m2;
    {
        Ov007Follower *b = link->to;
        int m3 = FX_MUL(damping, b->velocity.z);
        b->force.z -= nm1 + m3;
    }
}
