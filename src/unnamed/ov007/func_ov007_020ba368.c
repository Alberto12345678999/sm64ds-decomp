#include "types.h"
#include "nitro/fx/fx.h"
#include "Ov007Sprite.h"
extern u8 data_ov007_02104ba0[];
extern u8 data_ov007_02104b9c[];
extern s16 data_ov007_02104b98[];
extern u8 data_ov007_0210342c[];
extern short data_02082214[];

extern int _ZN4cstd3divEii(int, int);
extern int _ZN4cstd3modEii(int, int);
extern void func_ov007_020bdeb0(int a);
extern void func_ov007_020bda8c(int a, int b);
extern void func_ov007_020bfe4c(void *o, int x, int y, int z, void *out);
extern void func_ov007_020ba9bc(void);
extern int func_ov007_020c5854(int s, void *v, int a, int b, int c, int d);
extern void func_ov007_020c55bc(int a, int b, int c);

/* The 0xd0-byte touch picker func_ov007_020c690c builds (the scene's slot 0);
 * names as in func_ov007_020c684c, only the slots this function touches. */
typedef struct {
    int x, y, z;
} Vec3;
typedef struct Ov007Picker {
    char pad_00[8];
    int groupCount; /* 0x08 */
    char pad_0c[0xac];
    Vec3 boundsMin; /* 0xb8: the clamp rectangle (func_ov007_020c510c) */
    Vec3 boundsMax; /* 0xc4 */
} Ov007Picker;

/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates; names
 * as in func_ov007_020b91b4, only the slots this function touches. */
typedef struct Ov007PickerScene {
    Ov007Picker *picker; /* 0x00: func_ov007_020c690c */
    char pad_04[0x10];
    /* 0x14: func_ov007_020c5db0's point total over the stroke and every
     * group */
    int totalPoints;
    char pad_18[4];
    /* 0x1c: which 0x18-byte set of data_ov007_020d7b80 func_ov007_020ba9bc
     * binds as picker->springConstants (func_ov007_020c690c's a5); this
     * function picks 0/1/2/5/6 per phase */
    int springSet;
    /* 0x20: steps 0..4 each time this intro starts (t == 0) and picks its
     * shape: 0/3 squash along x/y, 1/4 spring pull, 2 wobble;
     * func_ov007_020b8fd4 slides sprites[1] in along x for 0, y for 3 */
    int introVariant;
} Ov007PickerScene;

/* data_ov007_02104b9c: the 0x14 record of the scene's sprites
 * (func_ov007_020b9880); names as in func_ov007_020b91b4. */
typedef struct Ov007PickerSprites {
    /* 0x00, medium confidence: Q12; func_ov007_020b8fd4 slides sprites[1]
     * in while it is <= 0x1000 */
    s32 slideProgress;
    Ov007Sprite *sprites[4]; /* 0x04: func_ov007_020c44e4 */
} Ov007PickerSprites;

/* The overlay's camera (func_ov007_020c023c); names as in
 * func_ov007_020b9ca8, only the slot this function reads. */
typedef struct Ov007Camera {
    char pad_00[0x2c];
    int distance; /* 0x2c: func_ov007_020bffb8 places the eye this far from the target */
} Ov007Camera;

/* data_ov007_0210342c: the overlay's manager; only its cameras here. */
typedef struct Ov007Work {
    char pad_00[0x30];
    Ov007Camera *cameras[2]; /* 0x30: func_ov007_020c023c */
} Ov007Work;

/* The externs keep the tree's array spelling (the declaration-agreement
 * gate); the typed views are reached through cast macros. */
#define SCENE (*(Ov007PickerScene **)data_ov007_02104ba0)
#define SPRITES (*(Ov007PickerSprites **)data_ov007_02104b9c)
#define WORK (*(Ov007Work **)data_ov007_0210342c)

int func_ov007_020ba368(int t)
{
    int s;
    int done = 0;
    int state;
    int local[3];

    {
        Ov007PickerScene *m = SCENE;
        s = (int)m->picker;
        m->springSet = 0;
    }

    if (t == 0) {
        int *p = &SCENE->introVariant;
        *p += 1;
        if (SCENE->introVariant >= 5) {
            SCENE->introVariant = 0;
        }
    }

    if (((Ov007Picker *)s)->groupCount == 0 || SCENE->totalPoints == 0) {
        int ratio;
        if (t <= 0) {
            ratio = 0;
        } else if (t >= 0x1e) {
            ratio = 0x1000;
        } else {
            ratio = _ZN4cstd3divEii(t << 0xc, 0x1e);
        }
        SPRITES->sprites[1]->alpha = ratio * 0x1f;
        return ratio >= 0x1000;
    }

    state = SCENE->introVariant;
    switch (state) {
    case 0:
    case 3:
    {
        int *p1 =
            (state == 0) ? &((Ov007Picker *)s)->boundsMin.x : &((Ov007Picker *)s)->boundsMin.y;
        int *p2 =
            (state == 0) ? &((Ov007Picker *)s)->boundsMax.x : &((Ov007Picker *)s)->boundsMax.y;
        int d, ratio, ease, v1, v2;
        v1 = *p1;
        v2 = *p2;
        d = v2 - v1;
        if (t <= 0) {
            ratio = 0;
        } else if (t >= 0x28) {
            ratio = 0x1000;
        } else {
            ratio = _ZN4cstd3divEii(t << 0xc, 0x28);
        }
        ease = (int)(((s64)ratio * (0x2000 - ratio)) >> 0xc);
        SCENE->springSet = 1;
        if (t == 0) {
            SPRITES->sprites[1]->alpha = 0x1f000;
            func_ov007_020bdeb0(0x1b);
        }
        *p2 = d / 2 - FX_MUL(ease, d);
        *p1 = *p2 - d * 2;
        func_ov007_020ba9bc();
        *p1 = v1;
        *p2 = v2;
        SPRITES->slideProgress = ease;
        done = ratio >= 0x1000;
        break;
    }
    case 1:
    case 4:
    {
        int r8arg, v, ratio;
        if (t <= 0) {
            ratio = 0;
        } else if (t >= 0x78) {
            ratio = 0x1000;
        } else {
            ratio = _ZN4cstd3divEii(t << 0xc, 0x78);
        }
        if (t == 0) {
            SPRITES->slideProgress = 0x1000;
            *(s16 *)data_ov007_02104b98 = -1;
        }
        if (t >= 0x96) {
            SCENE->springSet = 6;
        } else {
            SCENE->springSet = 0;
        }
        {
            Ov007Camera *o = WORK->cameras[0];
            func_ov007_020bfe4c(o, 0xe8000, 0xa8000, -o->distance, local);
        }
        func_ov007_020ba9bc();
        if (t <= 0xc8) {
            v = 0;
        } else if (t >= 0x258) {
            v = 0x1000;
        } else {
            v = _ZN4cstd3divEii((t - 0xc8) << 0xc, 0x190);
        }
        ratio += FX_MUL(v, 0x1e000);
        r8arg = 0x1000;
        if (SCENE->introVariant == 4) {
            if (t <= 0xc8) {
                if (t <= 0x64) {
                    ratio = FX_MUL(ratio, 0x258);
                    r8arg = -0xa;
                } else {
                    ratio = FX_MUL(ratio, 0x320);
                    r8arg = -0x32;
                }
            } else if (t <= 0x12c) {
                ratio = FX_MUL(ratio, 0xa);
            }
        }
        {
            int ret = func_ov007_020c5854(s, local, (ratio * 0xc8) >> 0xc, 0x2000, ratio * 0x12c, r8arg);
            int dv = _ZN4cstd3divEii(ret << 0xc, SCENE->totalPoints);
            SPRITES->sprites[1]->alpha = dv * 0x1f;
            if (dv >= 0x1000) {
                s16 c = *(s16 *)data_ov007_02104b98;
                if (c < 0) {
                    *(s16 *)data_ov007_02104b98 = 0;
                    func_ov007_020bdeb0(0x1e);
                } else {
                    *(s16 *)data_ov007_02104b98 = c + 1;
                    if (*(s16 *)data_ov007_02104b98 >= 0x1e) {
                        done = 1;
                    }
                }
                func_ov007_020bda8c(*(s16 *)data_ov007_02104b98, 1);
            } else {
                func_ov007_020bda8c(t, 0);
            }
        }
        break;
    }
    case 2:
    {
        int a = 0x1000;
        int b = 0x1000;
        if (t == 0) {
            SPRITES->slideProgress = 0x1000;
        }
        if (t <= 0x50) {
            int ratio, m, mc, r2c, ease1, ease2, term, sinval;
            u32 u;
            int idx;
            short tblval;
            if (t <= 0) {
                ratio = 0;
            } else if (t >= 0x28) {
                ratio = 0x1000;
            } else {
                ratio = _ZN4cstd3divEii(t << 0xc, 0x28);
            }
            ease1 = (int)(((s64)ratio * (0x2000 - ratio)) >> 0xc);
            m = _ZN4cstd3modEii(t, 6);
            if (m <= 0) {
                mc = 0;
            } else if (m >= 6) {
                mc = 0x1000;
            } else {
                mc = _ZN4cstd3divEii(m << 0xc, 6);
            }
            if (t <= 0x14) {
                r2c = 0;
            } else if (t >= 0x3c) {
                r2c = 0x1000;
            } else {
                r2c = _ZN4cstd3divEii((t - 0x14) << 0xc, 0x28);
            }
            ease2 = (int)(((s64)r2c * (0x2000 - r2c)) >> 0xc);
            u = (u32)(mc * 0xffff);
            u = u << 4;
            u = u >> 0x10;
            idx = (int)u >> 4;
            tblval = data_02082214[idx * 2];
            term = FX_MUL(ease2, 0x3e8);
            sinval = FX_MUL(tblval, term);
            if (t <= 0x4d) {
                sinval += FX_MUL(ease1, 0x4b0);
                a += sinval;
                b += sinval;
            } else {
                a = 0x2000;
                b = 0x2000;
            }
            SCENE->springSet = 2;
        } else {
            int v;
            if (t <= 0x50) {
                v = 0;
            } else if (t >= 0x64) {
                v = 0x1000;
            } else {
                v = _ZN4cstd3divEii((t - 0x50) << 0xc, 0x14);
            }
            a -= v;
            b -= v;
            if (t == 0x51) {
                func_ov007_020bdeb0(0x1f);
            }
            SCENE->springSet = 5;
            SPRITES->sprites[1]->alpha = v * 0x1f;
            if (v >= 0x1000) {
                done = 1;
            }
        }
        func_ov007_020c55bc(s, a, b);
        func_ov007_020ba9bc();
        break;
    }
    }
    return done;
}
