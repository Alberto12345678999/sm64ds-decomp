#include "Ov007StrokePath.h"

/* The lower allocator's legacy integer-address return remains a separate
 * interface-reconstruction dependency. */
extern void *func_ov007_020c2c68(int a, int b, int c);

void *func_ov007_020c2b9c(int pointCount, const int *progressThresholds) {
    int flags = 0;
    Ov007StrokePath *path;
    if (progressThresholds != 0)
        flags |= OV007_PATH_HAS_PROGRESS;
    path = (Ov007StrokePath *)func_ov007_020c2c68(OV007_PATH_PLANAR, pointCount, flags);
    if ((flags & OV007_PATH_HAS_PROGRESS) != 0) {
        int i;
        for (i = 0; i < pointCount; i++) {
            path->progressThresholds[i] = progressThresholds[i];
        }
    }
    path->pointCount = (u16)pointCount;
    return path;
}
