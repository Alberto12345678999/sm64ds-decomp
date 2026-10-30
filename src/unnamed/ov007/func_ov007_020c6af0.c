#include "Ov007Picker.h"

extern void MultiCopy_Int(int *src, int *dst, int len);

/* Copies each group's live points into groupPointCopies (MultiCopy_Int is
 * (src, dst)) and snapshots pos as restPos. */
void func_ov007_020c6af0(Ov007Picker *c) {
    int i;
    for (i = 0; i < c->groupCount; i++) {
        MultiCopy_Int((int *)c->groupPoints[i], (int *)c->groupPointCopies[i],
                      c->groups[i]->pointCount * 0xc);
    }
    c->restPos = c->pos;
}
