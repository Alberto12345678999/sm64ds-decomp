// @symbol func_ov007_020c6314
#include "Ov007Picker.h"

extern void SubVec3(Vector3 *a, Vector3 *b, Vector3 *c);
extern int LenVec3(Vector3 *v);

/* Re-measures group idx's links: from restPos to each rest point (flag 0),
 * between their own end points (flag 1), or from restPos to each live point
 * (flag 2). The parameter keeps the tree's char * spelling (the
 * declaration-agreement gate); the typed view is a local. */
void func_ov007_020c6314(char* t, int idx, int flag)
{
    Ov007Picker *self = (Ov007Picker *)t;
    int i;
    Ov007Link *e;

    switch (flag) {
    case 0:
        for (i = 0; i < self->groups[idx]->pointCount; i++) {
            e = self->groupLinks[idx][i];
            SubVec3(&self->restPos, &self->groupPointCopies[idx][i], &e->dir);
            e->length = LenVec3(&e->dir);
        }
        break;
    case 1:
        for (i = 0; i < self->groups[idx]->pointCount; i++) {
            e = self->groupLinks[idx][i];
            SubVec3(e->from->target, e->to->target, &e->dir);
            e->length = LenVec3(&e->dir);
        }
        break;
    case 2:
        for (i = 0; i < self->groups[idx]->pointCount; i++) {
            e = self->groupLinks[idx][i];
            SubVec3(&self->restPos, &self->groupPoints[idx][i], &e->dir);
            e->length = LenVec3(&e->dir);
        }
        break;
    }
}
