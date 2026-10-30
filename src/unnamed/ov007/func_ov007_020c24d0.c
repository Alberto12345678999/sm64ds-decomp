#include "Ov007StrokePath.h"

extern void func_ov007_020c2d44(Ov007StrokePath *path, int n);

/* One 12-byte point of the alternate representation's pointStorage. */
typedef struct Ov007PathPoint {
    int x, y, z;
} Ov007PathPoint;

/* Removes point idx from the path, shifting every later point (and its
 * segment length and progress threshold) down one; a planar path then
 * recomputes the segment that now ends at idx. */
void func_ov007_020c24d0(Ov007StrokePath *path, int idx) {
    int *lengths;
    int *xs;
    int *ys;
    unsigned short *angles;
    int i;

    if (path->pointCount == 0)
        return;
    if (idx >= path->pointCount)
        return;
    path->pointCount--;
    if (idx == path->pointCount)
        return;

    /* The round trip through long long is load-bearing: it gives i its own
     * register apart from idx, which the plain copy and a for loop do not. */
    i = (int)(long long)idx;
    while (i < path->pointCount) {
        switch (path->representation) {
        case OV007_PATH_PLANAR:
            xs = path->xCoords;
            xs[i] = xs[i + 1];
            ys = path->yCoords;
            ys[i] = ys[i + 1];
            angles = path->segmentAngles;
            angles[i] = angles[i + 1];
            break;
        case 1:
            ((Ov007PathPoint *)path->pointStorage)[i] =
                ((Ov007PathPoint *)path->pointStorage)[i + 1];
            break;
        }
        lengths = path->segmentLengths;
        lengths[i] = lengths[i + 1];
        if (path->flags & OV007_PATH_HAS_PROGRESS)
            path->progressThresholds[i] = path->progressThresholds[i + 1];
        i++;
    }

    switch (path->representation) {
    case OV007_PATH_PLANAR:
        func_ov007_020c2d44(path, idx);
        break;
    case 1:
        break;
    }
}
