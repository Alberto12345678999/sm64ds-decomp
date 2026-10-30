#include "Ov007StrokePath.h"

extern void func_ov007_020c2d44(Ov007StrokePath *path, int n);

/* Recomputes every segment of a planar path (func_ov007_020c2d44). */
void func_ov007_020c27b4(Ov007StrokePath *path) {
    int i;
    switch (path->representation) {
    case OV007_PATH_PLANAR:
        for (i = 0; i < path->pointCount; i++)
            func_ov007_020c2d44(path, i);
        break;
    case 1:
        break;
    }
}
