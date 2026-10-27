#include "types.h"
#include "nitro/fx/fx.h"

extern int func_020531a4(int a);
extern int fdiv(int a, int b);

typedef struct S {
    Vector3 *p;
    int f4;
    int f8;
    int fc;
    int f10;
    int f14;
    int f18;
} S;

int func_ov007_020c704c(S *self, Vector3 *b, int r2arg, int r3arg, int radius) {
    int dx, dy, sum, spd, ratio;
    s64 sdx, sdy;

    dx = b->x - self->p->x;
    dy = b->y - self->p->y;
    sum = FX_MUL(dx, dx) + FX_MUL(dy, dy);
    sdx = dx;
    sdy = dy;

    if (sum <= FX_MUL(radius, radius)) {
        self->f18 = 0;
        self->f14 = self->f18;
        self->f10 = self->f14;
        self->fc = self->f10;
        self->f8 = self->fc;
        self->f4 = self->f8;
        *self->p = *b;
        return 2;
    }

    if (sum <= FX_MUL(r3arg, r3arg)) {
        spd = func_020531a4(sum);
        ratio = fdiv(r2arg, spd);

        self->f10 += FX_MUL(ratio, sdx);
        self->f14 += FX_MUL(ratio, sdy);
        return 1;
    }
    return 0;
}
