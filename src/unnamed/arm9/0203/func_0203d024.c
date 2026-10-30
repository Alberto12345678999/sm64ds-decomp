#include "types.h"

/* 1 if two Vector3s differ in any component, else 0. daStar_c tests a
   centre against zero with it. */
int func_0203d024(Vector3 *a, Vector3 *b) {
    if (a->x != b->x || a->y != b->y || a->z != b->z) return 1;
    return 0;
}
