#include "Ov007Picker.h"

/* The point total over the stroke being drawn and every committed group. */
int func_ov007_020c5db0(Ov007Picker *c) {
    int i;
    int total;
    int count;
    total = c->path->pointCount;
    count = c->groupCount;
    i = 0;
    if (count > 0) {
        do {
            Ov007StrokePath *e = c->groups[i];
            i++;
            total += e->pointCount;
        } while (i < count);
    }
    return total;
}
