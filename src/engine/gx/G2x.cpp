//cpp
/* engine/gx/G2x.cpp — G2x TU (arm9 0x02055238..0x0205532c)
 *
 * G2x has no instance state: every member is static and writes the 2D
 * engine's blend/affine registers through the caller's `volatile u16*`
 * (include/G2x.h). The file is written ROM-descending because mwccarm
 * emits .text in reverse source order under default deferred codegen.
 */
#include "G2x.h"
#include "types.h"

struct Matrix2x2 { int m[4]; };

// @symbol _ZN3G2x12SetBGyAffineEPVtP9Matrix2x2iiii
void G2x::SetBGyAffine(volatile unsigned short *p, Matrix2x2 *m, int a, int b, int c, int d)
{
    u16 pa = (u16)(s16)(m->m[0] >> 4);
    u16 pb = (u16)(s16)(m->m[1] >> 4);
    *(volatile unsigned int *)p = pa | (pb << 16);

    u16 pc = (u16)(s16)(m->m[2] >> 4);
    u16 pd = (u16)(s16)(m->m[3] >> 4);
    *(volatile unsigned int *)(p + 2) = pc | (pd << 16);

    int dx = c - a;
    int dy = d - b;
    int x = m->m[0] * dx + m->m[1] * dy + (a << 12);
    int y = m->m[2] * dx + m->m[3] * dy + (b << 12);

    *(volatile int *)(p + 4) = x >> 4;
    *(volatile int *)(p + 6) = y >> 4;
}

// @symbol _ZN3G2x13SetBlendAlphaEPVttttj
void G2x::SetBlendAlpha(volatile u16 *reg, u16 firstTarget,
                        u16 secondTarget, u16 firstAlpha,
                        u32 secondAlpha)
{
    *(volatile u32 *)reg =
        ((firstTarget | 0x40) | (secondTarget << 8)) |
        ((firstAlpha | (secondAlpha << 8)) << 16);
}

// @symbol _ZN3G2x18SetBlendBrightnessEPVtts
void G2x::SetBlendBrightness(volatile unsigned short *p, unsigned short val, short amt)
{
    if (amt < 0) {
        p[0] = val | 0xc0;
        p[2] = -amt;
    } else {
        p[0] = val | 0x80;
        p[2] = amt;
    }
}
