#include "nitro/fx/fx.h"
#include "Ov007Spring.h"

/* func_ov007_020c7560's mode 2: a damped spring in x and y. The offset of
 * from - to past dir, times stiffness (Q12), pulls it back toward dir: from
 * gets -stiffness * (offset - dir) and to the opposite. Each end is damped
 * by its own velocity times damping. */
void func_ov007_020c7b2c(Ov007Link *link, int stiffness, int damping) {
    int dx;
    int dy;
    int fx;
    int fy;

    dx = link->from->target->x - link->to->target->x - link->dir.x;
    dy = link->from->target->y - link->to->target->y - link->dir.y;
    fx = -FX_MUL(stiffness, dx);
    fy = -FX_MUL(stiffness, dy);
    link->from->force.x += fx - FX_MUL(damping, link->from->velocity.x);
    link->from->force.y += fy - FX_MUL(damping, link->from->velocity.y);
    link->to->force.x -= fx + FX_MUL(damping, link->to->velocity.x);
    link->to->force.y -= fy + FX_MUL(damping, link->to->velocity.y);
}
