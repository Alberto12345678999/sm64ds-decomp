#include "Ov007Picker.h"

extern void func_ov007_020c6af0(Ov007Picker *c);
extern void func_ov007_020c6b58(Ov007Picker *c);
/* The definitions spell the picker char *; void * here spares the casts. */
extern void func_ov007_020c64c4(void *c, int b);
extern void func_ov007_020c62cc(void *c, int b);

/* Rebuilds the picker's links from its rest points (func_ov007_020c6af0,
 * func_ov007_020c6b58, func_ov007_020c64c4, func_ov007_020c62cc), then
 * stops every point and clears posOffset. */
void func_ov007_020c5ef0(Ov007Picker *c) {
    int i, j;
    func_ov007_020c6af0(c);
    func_ov007_020c6b58(c);
    func_ov007_020c64c4(c, 0);
    func_ov007_020c62cc(c, 1);
    for (i = 0; i < c->groupCount; i++) {
        Ov007PointList *in = c->pointLists[i];
        for (j = 0; j < in->count; j++) {
            Ov007Follower *o = in->items[j];
            o->force.z = 0;
            o->force.y = o->force.z;
            o->force.x = o->force.y;
            o->velocity.z = o->force.x;
            o->velocity.y = o->velocity.z;
            o->velocity.x = o->velocity.y;
        }
    }
    c->posOffset.z = 0;
    c->posOffset.y = c->posOffset.z;
    c->posOffset.x = c->posOffset.y;
}
