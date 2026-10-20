#include "types.h"
#include "nitro/fx/fx.h"
#include "Ov007MenuState.h"
#include "Ov007Sprite.h"
#include "Ov007Touch.h"
#pragma opt_strength_reduction off

extern int func_ov007_020c1da0(int i);
extern int func_020531a4(int a);
extern int _ZN4cstd3divEii(int a, int b);
extern void func_ov007_020bed60(int a, int b, int c);
extern char *func_ov007_020b2cdc(void);
extern void func_ov007_020ca1d4(char *self, int a);
extern void func_ov007_020cba78(char *c, int a);
extern void func_ov007_020bf57c(char *a, int idx);
extern void func_ov007_020c9c24(char *a, int b);
extern void func_ov007_020c9a84(char *a, char *b, char *c, char *d);
extern void func_ov007_020bce70(int n, int m);
extern unsigned short func_ov007_020c3be0(int t, int a, int b);

/* The 0x2c-byte record func_ov007_020aea6c allocates; only the slots this
 * file touches. */
typedef struct Ov007Item {
    char pad_00[4];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388(1) */
    s32 posX;              /* 0x08: Q12; func_ov007_020ae810 seeds it from the layout */
    s32 posY;              /* 0x0c */
    char pad_10[0x10];
    s32 ready; /* 0x20: func_ov007_020ae834 sets it once the state settles and
                * clears it on reset; medium confidence */
} Ov007Item;

/* The 0x1c record func_ov007_020b4c04 returns (names as in that file). */
typedef struct Ov007ItemView {
    Ov007Item *item;     /* 0x00 */
    Ov007Sprite *sprite; /* 0x04 */
} Ov007ItemView;

/* The 0x28-byte light func_ov007_020c241c allocates; func_ov007_020c232c
 * writes +0x22 to LIGHT_COLOR. Only that slot is spelled. */
typedef struct Ov007Light {
    char pad_00[0x22];
    u16 color; /* 0x22 */
} Ov007Light;

/* data_ov007_0210342c: the overlay's manager. No class or header names it;
 * only the slots this file touches are spelled. */
typedef struct Ov007Work {
    char pad_00[4];
    Ov007MenuState *states[3]; /* 0x04: func_ov007_020c9388 */
    char pad_10[0x20];
    void *cameras[2];             /* 0x30: func_ov007_020c023c */
    Ov007Light *lights[2];        /* 0x38: func_ov007_020c241c(0/1) */
    Ov007MenuState *paletteState; /* 0x40: func_ov007_020bce70 requests palette n on
                                   * it and blends over its stateTicks */
    char pad_44[0xc];
    Ov007Touch *touch; /* 0x50: func_ov007_020c2068 */
    char pad_54[0xc0];
    Ov007ItemView *itemViews[0x18]; /* 0x114: one per func_ov007_020b4c04 */
} Ov007Work;

extern u8 data_ov007_0210342c[];
extern u8 data_ov007_02104bd4[];
/* The extern keeps the tree's u8[] spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK (*(Ov007Work **)data_ov007_0210342c)

void func_ov007_020beeb0(void)
{
    int sp0;
    int sp4;
    int sp8;
    int r4;

    r4 = *(int *)(*(char **)data_ov007_02104bd4);

    if (WORK->touch->cur.touch != 0) {
        int r6;
        Ov007Touch *base;
        if (func_ov007_020c1da0(0) == 0)
            r6 = 0x1000;
        else
            r6 = 0xbb8;
        base = WORK->touch;
        if (base->heldFrames != 0) {
            int s2 = base->deltaY;
            int s1 = base->deltaX;
            int d = _ZN4cstd3divEii(func_020531a4((s1 * s1 + s2 * s2) << 0xc), 0x1e);
            int r2 = FX_MUL(r6, d);
            if (r2 >= 0x1000)
                r2 = 0x1000;
            r6 = (int)(((s64)r2 * r2) >> 0xc);
        }
        base = WORK->touch;
        func_ov007_020bed60(base->cur.x, base->cur.y, r6);
    } else {
        char *p = func_ov007_020b2cdc();
        int a;
        if (*(int *)(p + 0xc) == 0) {
            a = *(short *)p;
            if (a >= 0 && a < 0x18) {
                a = *(short *)(p + 0xa);
                if (a >= 0 && a < 0x18) {
                    Ov007ItemView *q = WORK->itemViews[a];
                    Ov007Item *v = q->item;
                    func_ov007_020bed60(v->posX >> 0xc, v->posY >> 0xc, 0x7d0);
                }
            }
        }
    }

    func_ov007_020ca1d4(*(char **)(*(char **)data_ov007_02104bd4 + 0xc), r4);
    func_ov007_020cba78((char *)r4, 2);

    for (int i = 0; i < 8; i++) {
        char *r8p = *(char **)(*(char **)data_ov007_02104bd4 + i * 4 + 0x10);
        Ov007ItemView *r6p = WORK->itemViews[i + 0xe];
        Ov007Sprite *w;
        int t;
        if (r6p->item->state->stateWork == 2)
            func_ov007_020bf57c((char *)WORK->cameras[0], i);
        if (r6p->item->ready != 0) {
            func_ov007_020c9c24(r8p, 2);
            w = r6p->sprite;
            func_ov007_020c9a84(r8p, (char *)&w->posOffset, (char *)&w->rotX, (char *)&w->rotY);
            w = r6p->sprite;
            t = w->posOffset.x;
            w->posOffset.x = FX_MUL(t, 0x64);
            w = r6p->sprite;
            t = w->posOffset.y;
            w->posOffset.y = FX_MUL(t, 0x64);
        }
    }

    int r5;
    switch (WORK->states[1]->currentState) {
    case 0:
    case 1:
    case 11:
    case 12:
        sp0 = 4;
        r5 = 0x1e;
        sp4 = 0x7fff;
        sp8 = 0x4800;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        sp0 = 5;
        r5 = 0x3c;
        sp4 = 0x575c;
        sp8 = 0x178;
        break;
    case 7:
    case 8:
        sp0 = 6;
        r5 = 0x3c;
        sp4 = 0x631a;
        sp8 = 0x7fbf;
        break;
    case 9:
    case 10:
        r5 = 0x3c;
        sp4 = 0x7fff;
        sp8 = 0x49e0;
        sp0 = 7;
        break;
    default:
        break;
    }

    func_ov007_020bce70(sp0, r5);

    {
        char *o8 = *(char **)(*(char **)data_ov007_02104bd4 + 8);
        int n = WORK->paletteState->stateTicks;
        u16 *p7 = (u16 *)(o8 + 0x28);
        u16 *p6 = (u16 *)(o8 + 0x2a);
        int ratio;
        if (n <= 0)
            ratio = 0;
        else if (n >= r5)
            ratio = 0x1000;
        else
            ratio = _ZN4cstd3divEii(n << 0xc, r5);
        *p7 = func_ov007_020c3be0(ratio, *p7, sp4);
        *p6 = func_ov007_020c3be0(ratio, *p6, sp8);
    }

    {
        int r0;
        Ov007MenuState *t2 = WORK->states[2];
        int r4v = 0x7fff;
        r0 = 0x1000;
        int s = t2->currentState;
        if (s == 0xb) {
            int n = t2->stateTicks;
            r4v = 0x3def;
            if (n <= 0)
                r0 = 0;
            else if (n < 0x1e)
                r0 = _ZN4cstd3divEii(n << 0xc, 0x1e);
        } else if (s == 0xa) {
            int n = t2->stateTicks;
            if (n <= 0)
                r0 = 0;
            else if (n < 0x1e)
                r0 = _ZN4cstd3divEii(n << 0xc, 0x1e);
        }
        WORK->lights[0]->color = func_ov007_020c3be0(r0, WORK->lights[0]->color, r4v);
    }
}
