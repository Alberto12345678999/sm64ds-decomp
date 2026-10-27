//cpp
// @symbol func_020092c4
/* recovered: shared common types */
#include "common.h"
#include "cstd.h"

extern "C" {

extern void Vec3_Sub(struct Vector3 *out, struct Vector3 *a, struct Vector3 *b);
extern int LenVec3(struct Vector3 *v);
extern int Math_Function_0203b14c(int *a, int b, int c, int d, int e);
extern void Vec3_MulScalarInPlace(int *v, int s);
extern void Vec3_Add(struct Vector3 *out, struct Vector3 *a, struct Vector3 *b);

int func_020092c4(int arg0, struct Vector3 *out, struct Vector3 *target)
{
    struct Vector3 d;
    int len;
    int r5;
    int scratch;
    Vec3_Sub(&d, out, target);
    len = LenVec3(&d);
    if (len == 0) return 1;
    scratch = len;
    r5 = Math_Function_0203b14c(&scratch, 0, 0x200, 0x40000, 0x8000);
    Vec3_MulScalarInPlace((int *)&d, cstd::fdiv(scratch, len));
    {
        struct Vector3 res;
        Vec3_Add(&res, target, &d);
        out->x = res.x;
        out->y = res.y;
        out->z = res.z;
    }
    return r5 == 0 ? 1 : 0;
}
}
