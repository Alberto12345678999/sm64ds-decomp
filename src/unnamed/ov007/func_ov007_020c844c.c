/* The 0x24-byte follower record allocated below; names as in
 * func_ov007_020c83fc, which resets it. */
typedef struct Ov007Follower {
    int *target;     /* 0x00 */
    int velocity[3]; /* 0x04 */
    int force[3];    /* 0x10 */
    short invMass;   /* 0x1c: Q12 */
    unsigned short pad_1e;
    int flags; /* 0x20 */
} Ov007Follower;

extern void *func_ov007_020c3df4(int a, int b);
extern void func_ov007_020c83fc(void *o);
extern short func_02053200(int x);

/* Builds a follower that moves the Q12 position at p, with mass q (Q12):
 * invMass is its fixed-point reciprocal (func_02053200), 0x1000 directly
 * for q = 1.0. p keeps the callers' int spelling. */
void *func_ov007_020c844c(int p, int q) {
    Ov007Follower *f = (Ov007Follower *)func_ov007_020c3df4(0, sizeof(Ov007Follower));
    func_ov007_020c83fc(f);
    f->target = (int *)p;
    if (q == 0x1000)
        f->invMass = 0x1000;
    else
        f->invMass = func_02053200(q);
    return f;
}
