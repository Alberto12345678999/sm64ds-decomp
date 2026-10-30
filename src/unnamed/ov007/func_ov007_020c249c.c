#include "Ov007StrokePath.h"

/* The path's length: the sum of its segment lengths, taken over all
 * pointCount entries. */
int func_ov007_020c249c(Ov007StrokePath *path) {
    int i;
    int sum = 0;
    unsigned short n = path->pointCount;
    for (i = 0; i < n; i++) {
        sum = sum + path->segmentLengths[i];
    }

    return sum;
}
