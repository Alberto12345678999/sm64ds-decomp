#include "Ov007StrokePath.h"

extern void func_ov007_020c2d44(void *obj, int i);

void *func_ov007_020c2b38(int pointCount, const int *xCoords, const int *yCoords,
                          const int *progressThresholds) {
    Ov007StrokePath *path = (Ov007StrokePath *)func_ov007_020c2b9c(pointCount, progressThresholds);
    int i;
    for (i = 0; i < pointCount; i++) {
        path->xCoords[i] = xCoords[i];
        path->yCoords[i] = yCoords[i];
        func_ov007_020c2d44(path, i);
    }
    return path;
}
