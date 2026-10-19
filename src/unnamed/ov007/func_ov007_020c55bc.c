#include "types.h"

struct Elem {
    int _0;
    int count;
};

struct Self {
    int _0[2];
    int f8;
    int _c[8];
    Vector3 **f2c;
    int _30;
    int ***f34;
    int _38;
    struct Elem **f3c;
    int _40[15];
    int f7c;
    int f80;
};

void func_ov007_020c55bc(struct Self *self, int m1, int m2)
{
    int i;
    int j;
    int b7c, b80;
    int x, y;
    int dx, dy;
    int *p;
    int *q;
    long long M1, M2;

    i = 0;
    if (self->f8 <= 0)
        return;

    M1 = m1;
    M2 = m2;

    do {
        j = 0;
        if (self->f3c[i]->count > 0) {
            do {
                p = self->f34[i][j];
                q = (int *)(((int)p + 0xc));
                b7c = self->f7c;
                b80 = self->f80;
                x = self->f2c[i][j].x;
                y = self->f2c[i][j].y;
                dx = b7c - x;
                dy = b80 - y;

                /* Not FX_MUL: its (fx64) recast of the s64 M1/M2 moves a register (6 words differ). */
                q[0] = (int)((M1 * dx + 0x800) >> 12);
                q[1] = (int)((M2 * dy + 0x800) >> 12);
                j++;
            } while (j < self->f3c[i]->count);
        }
        i++;
    } while (i < self->f8);
}
