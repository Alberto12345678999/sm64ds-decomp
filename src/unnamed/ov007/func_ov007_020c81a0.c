#include "nitro/fx/fx.h"
#include "Ov007Spring.h"

/* One damped Euler step in x and y, as func_ov007_020c80c8 does z:
 * damping is the factor, shift the step shift. Force is cleared either way. */
void func_ov007_020c81a0(Ov007Follower *f, int damping, int shift) {
    if (!(f->flags & 1)) {
        if (f->invMass == 0x1000) {
            f->velocity.x += (f->force.x - FX_MUL(damping, f->velocity.x)) >> shift;
            f->velocity.y += (f->force.y - FX_MUL(damping, f->velocity.y)) >> shift;
        } else {
            f->force.x -= FX_MUL(damping, f->velocity.x);
            f->force.y -= FX_MUL(damping, f->velocity.y);
            f->velocity.x += FX_MUL(f->force.x, (f->invMass >> shift));
            f->velocity.y += FX_MUL(f->force.y, (f->invMass >> shift));
        }
        f->target->x += f->velocity.x >> shift;
        f->target->y += f->velocity.y >> shift;
    }

    f->force.y = 0;
    f->force.x = f->force.y;
}
