#include "types.h"
#include "Ov007Model.h"

/* Resets the placement: pos and rotation 0, scale 1 (Q12). */
void func_ov007_020bc434(Ov007Model *m) {
    m->pos.z = 0;
    m->pos.y = m->pos.z;
    m->pos.x = m->pos.y;
    m->scale.z = 0x1000;
    m->scale.y = m->scale.z;
    m->scale.x = m->scale.y;
    m->rotZ = 0;
    m->rotY = m->rotZ;
    m->rotX = m->rotY;
}
