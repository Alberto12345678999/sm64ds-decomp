#include "types.h"
typedef struct {
    int pad0[3];
    Vector3 a;
    int pad1[2];
    Vector3 b;
    Vector3 c;
    Vector3 d;
    Vector3 e;
} T;
void func_ov007_020c9f10(T *self, Vector3 *pos, int w, int h) {
    Vector3 *pe = &self->e;
    Vector3 *pd = &self->d;
    Vector3 *pc = (Vector3 *)(((int)self + 0x2c));
    int* qd = (int*)(((int)self + 0x3c));
    int* qe = (int*)(((int)self + 0x48));
    *pe = *pos;
    *pd = *pe;
    *pc = *pd;
    {
        Vector3 *pb = (Vector3 *)(((int)self + 0x20));
        *pb = *pc;
        self->a = *pb;
        pb->x -= w / 2;
        pc->x += w / 2;
        *qd -= h / 2;
        *qe += h / 2;
    }
}
