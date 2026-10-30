#include "nitro/fx/fx.h"
#include "Ov007StrokePath.h"

extern int func_020538b8(int x, int y);
extern int func_020531a4(int a);

/* Recomputes segment n of a planar path, the one ending at point n: its
 * length (func_020531a4, the Q12 square root) and its angle
 * (func_020538b8 on the x/y steps), stored negated. Point 0 has no segment;
 * when segment 1 is set, point 0 takes its angle. */
void func_ov007_020c2d44(Ov007StrokePath *path, int n) {
    int ang, dy, dx;
    if (n > 0) {
        dy = path->yCoords[n] - path->yCoords[n - 1];
        dx = path->xCoords[n] - path->xCoords[n - 1];
        ang = func_020538b8(dx, dy);
    } else {
        dx = 0;
        dy = 0;
        ang = 0;
    }
    int a = FX_MUL(dy, dy);
    int b = FX_MUL(dx, dx);
    int len = func_020531a4(a + b);
    path->segmentLengths[n] = len;
    path->segmentAngles[n] = -ang;
    if (n == 1) {
        path->segmentAngles[0] = path->segmentAngles[1];
    }
}
