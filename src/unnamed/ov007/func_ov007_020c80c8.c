#include "types.h"
#include "nitro/fx/fx.h"
#include "Ov007Spring.h"

/* One damped Euler step on the z axis, the z-only form of
 * func_ov007_020c831c: a is the damping factor, s the step shift. */
void func_ov007_020c80c8(Ov007Follower *f, int a, int s) {
    if (!(f->flags & 1)) {
        if (f->invMass == 0x1000) {
            f->velocity.z += (f->force.z - FX_MUL(a, f->velocity.z)) >> s;
        } else {
            f->force.z -= FX_MUL(a, f->velocity.z);
            f->velocity.z += FX_MUL(f->force.z, (f->invMass >> s));
        }
        f->target->z += f->velocity.z >> s;
    }
    f->force.z = 0;
}
