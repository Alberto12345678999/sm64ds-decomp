/* One of the arm9 Vector3 helpers declared in include/math/CalcLib.h: shift a
   vector right per axis. Reads all three components before writing any, so it
   is safe to call with d == s. */
#include "types.h"

void Vec3_Asr(Vector3 *d, Vector3 *s, int sh) {
    int a = s->x;
    int b = s->y;
    int c = s->z;
    d->x = a >> sh;
    d->y = b >> sh;
    d->z = c >> sh;
}
