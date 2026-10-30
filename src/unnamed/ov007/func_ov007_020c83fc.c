#include "Ov007Spring.h"

/* Clears a follower: at rest, no target, unit inverse mass, no flags. */
void func_ov007_020c83fc(Ov007Follower *f) {
    f->force.z = 0;
    f->force.y = f->force.z;
    f->force.x = f->force.y;
    f->velocity.z = f->force.x;
    f->velocity.y = f->velocity.z;
    f->velocity.x = f->velocity.y;
    f->target = 0;
    f->invMass = 0x1000;
    f->flags = 0;
}
