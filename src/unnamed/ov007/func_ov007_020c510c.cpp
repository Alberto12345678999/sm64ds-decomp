//cpp
#include "Ov007Picker.h"
#include "Ov007Camera.h"

extern "C" {
extern void func_ov007_020bfe4c(void *o, int x, int y, int z, void *out);

typedef struct {
    int x, y, z;
} Vec3;

/* Unprojects the camera's screen rectangle at the camera distance into the
   picker's clamp rectangle; screen y runs down, so the two y bounds swap. */
void func_ov007_020c510c(char *c) {
    Ov007Picker *p = (Ov007Picker *)c;
    int neg;
    Ov007Camera *o = p->camera;
    neg = -o->distance;
    func_ov007_020bfe4c(o, o->viewportMinX << 0xc, o->viewportMinY << 0xc, neg, &p->boundsMin);
    func_ov007_020bfe4c(o, o->viewportMaxX << 0xc, o->viewportMaxY << 0xc, neg, &p->boundsMax);
    {
        int t = p->boundsMin.y;
        p->boundsMin.y = p->boundsMax.y;
        p->boundsMax.y = t;
    }
}
}
