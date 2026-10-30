#include "Ov007StrokePath.h"
#include "Ov007Picker.h"

void func_ov007_020c4fcc(int r0, int r1);
void func_ov007_020c19cc(int r0, int r1, int r2, int r3);

/* Draws every committed stroke but group idx, and the stroke being drawn,
 * in full under the first style (func_ov007_020c4fcc(a2, a3)); then group
 * idx on top under the second (a5, a6). thiz keeps the int * spelling of
 * the definition; `self` is the typed view. */
void func_ov007_020c4e98(int *thiz, int a1, int a2, int a3, int idx,
                         unsigned short a5, int a6)
{
    Ov007Picker *self = (Ov007Picker *)thiz;
    int i;
    Vector3 **base;
    base = self->groupPoints;
    func_ov007_020c4fcc(a2, a3);
    for (i = 0; i < self->groupCount; i++) {
        if (i == idx) continue;
        func_ov007_020c19cc(self->groups[i]->pointCount, (int)base[i], a1, 0x1000);
    }
    func_ov007_020c19cc(self->path->pointCount, (int)self->pathPoints, a1, 0x1000);
    func_ov007_020c4fcc(a5, a6);
    func_ov007_020c19cc(self->groups[idx]->pointCount, (int)base[idx], a1, 0x1000);
}
