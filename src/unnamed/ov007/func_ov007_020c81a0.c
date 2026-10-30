#include "nitro/fx/fx.h"

/* The 0x24-byte follower record func_ov007_020c844c allocates; names as in
 * func_ov007_020c83fc, which resets it. */
typedef struct Ov007Follower {
    int *target;     /* 0x00: the Q12 position each step moves */
    int velocity[3]; /* 0x04: added to target[] every step, >> shift */
    int force[3];    /* 0x10: accumulated per frame, cleared at the end of each step */
    short invMass;   /* 0x1c: Q12; 0x1000 takes the direct path */
    unsigned short pad_1e;
    int flags; /* 0x20: bit 0 skips the step (target held) */
} Ov007Follower;

/* One damped Euler step in x and y, as func_ov007_020c80c8 does z:
 * damping is the factor, shift the step shift. Force is cleared either way. */
void func_ov007_020c81a0(Ov007Follower *f, int damping, int shift) {
    if (!(f->flags & 1)) {
        if (f->invMass == 0x1000) {
            f->velocity[0] += (f->force[0] - FX_MUL(damping, f->velocity[0])) >> shift;
            f->velocity[1] += (f->force[1] - FX_MUL(damping, f->velocity[1])) >> shift;
        } else {
            f->force[0] -= FX_MUL(damping, f->velocity[0]);
            f->force[1] -= FX_MUL(damping, f->velocity[1]);
            f->velocity[0] += FX_MUL(f->force[0], (f->invMass >> shift));
            f->velocity[1] += FX_MUL(f->force[1], (f->invMass >> shift));
        }
        f->target[0] += f->velocity[0] >> shift;
        f->target[1] += f->velocity[1] >> shift;
    }

    f->force[1] = 0;
    f->force[0] = f->force[1];
}
