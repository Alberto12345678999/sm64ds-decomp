#include "nitro/fx/fx.h"

/* The 0x24-byte follower func_ov007_020c844c allocates; names as in
 * func_ov007_020c83fc, only the slots this file touches. */
typedef struct Ov007Follower {
    int *target;     /* 0x00: the Q12 position each step moves */
    int velocity[3]; /* 0x04 */
    int force[3];    /* 0x10: accumulated per frame */
} Ov007Follower;

/* A link between two points; names as in func_ov007_020c6314. */
typedef struct Ov007Link {
    Ov007Follower *from; /* 0x0 */
    Ov007Follower *to;   /* 0x4 */
    int length;          /* 0x8 */
    int dir[3];          /* 0xc: func_ov007_020c8010's from - to */
} Ov007Link;

/* func_ov007_020c7560's mode 2: a damped spring in x and y. The offset of
 * from - to past dir, times stiffness (Q12), pushes the two ends apart,
 * and each end is damped by its own velocity times damping. */
void func_ov007_020c7b2c(Ov007Link *link, int stiffness, int damping) {
    int dx;
    int dy;
    int fx;
    int fy;

    dx = link->from->target[0] - link->to->target[0] - link->dir[0];
    dy = link->from->target[1] - link->to->target[1] - link->dir[1];
    fx = -FX_MUL(stiffness, dx);
    fy = -FX_MUL(stiffness, dy);
    link->from->force[0] += fx - FX_MUL(damping, link->from->velocity[0]);
    link->from->force[1] += fy - FX_MUL(damping, link->from->velocity[1]);
    link->to->force[0] -= fx + FX_MUL(damping, link->to->velocity[0]);
    link->to->force[1] -= fy + FX_MUL(damping, link->to->velocity[1]);
}
