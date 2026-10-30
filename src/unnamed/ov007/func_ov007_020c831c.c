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

/* out = b + s * a, per component in Q12. */
extern void func_02053320(int s, int *a, int *b, int *out);

/* One damped Euler step in x, y and z, the 3D form of func_ov007_020c81a0;
 * here the direct path replaces velocity with the damped force. */
void func_ov007_020c831c(Ov007Follower *f, int damping, int shift) {
    if ((f->flags & 1) == 0) {
        func_02053320(-damping, f->velocity, f->force, f->force);
        if (f->invMass == 0x1000) {
            f->velocity[0] = f->force[0] >> shift;
            f->velocity[1] = f->force[1] >> shift;
            f->velocity[2] = f->force[2] >> shift;
        } else {
            func_02053320(f->invMass >> shift, f->force, f->velocity, f->velocity);
        }
        f->target[0] += f->velocity[0] >> shift;
        f->target[1] += f->velocity[1] >> shift;
        f->target[2] += f->velocity[2] >> shift;
    }
    f->force[2] = 0;
    f->force[1] = f->force[2];
    f->force[0] = f->force[1];
}
