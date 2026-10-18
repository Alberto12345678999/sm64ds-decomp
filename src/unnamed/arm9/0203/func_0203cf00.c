#include "types.h"

extern void CrossVec3(Vector3 *a, Vector3 *b, Vector3 *result);

void func_0203cf00(Vector3 *out, Vector3 *a, Vector3 *b) {
    Vector3 tmp;
    CrossVec3(a, b, &tmp);
    out->x = tmp.x;
    out->y = tmp.y;
    out->z = tmp.z;
}
