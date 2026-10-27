//cpp
#include "nitro/fx/fx.h"
#include "Ov007Work.h"
#include "cstd.h"

extern "C" {

typedef short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef long long s64;

extern u8 data_ov007_0210342c[];
extern u8 data_ov007_02104ba0[];
extern short data_02082214[];

extern void func_ov007_020bbc08(int a, int b, int c);
extern void func_ov007_020bdeb0(int a);
extern void func_ov007_020bde2c(int idx);
extern void func_ov007_020bda38(int v);
extern void func_020524e4(int *p, int a, int b);
extern void func_ov007_020c5490(char *obj, int *m);
extern void func_ov007_020c55bc(int a, int b, int c);
extern void func_ov007_020c6314(char *c, int i, int b);
extern void func_ov007_020c6174(char *a, int i, int b);

/* The pad record func_ov007_020c2304 fills; names as in func_ov007_020b2e64. */
typedef struct Ov007Pad {
    u16 keys;     /* 0x00: held this frame */
    u16 prevKeys; /* 0x02: held last frame */
    /* 0x04: frames each button has been held, 1 on the press frame; 0 while
     * it is up (func_ov007_020c20b8) */
    u32 heldFrames[12];
} Ov007Pad;

/* The 0xd0-byte touch picker func_ov007_020c690c builds; only its group
 * count here. */
typedef struct Ov007Picker {
    char pad_00[8];
    int groupCount; /* 0x08: committed strokes */
} Ov007Picker;

/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates; names
 * as in func_ov007_020ba05c, only the slots this function touches. */
typedef struct Ov007PickerScene {
    Ov007Picker *picker; /* 0x00: func_ov007_020c690c */
    char pad_04[0x18];
    /* 0x1c: which six-int row of data_ov007_020d7b80 func_ov007_020ba9bc
     * installs as the picker's springConstants (+0x18); this function picks
     * 0, 2 or 3 */
    int springSet;
} Ov007PickerScene;

typedef char Ov007Pad_size_must_be_0x34[sizeof(Ov007Pad) == 0x34 ? 1 : -1];
typedef char Ov007PickerScene_size_must_be_0x20[sizeof(Ov007PickerScene) == 0x20 ? 1 : -1];

/* The externs keep the tree's u8[] spelling; the typed views are reached
 * through cast macros. */
#define WORK (*(Ov007Work **)data_ov007_0210342c)
#define SCENE (*(Ov007PickerScene **)data_ov007_02104ba0)

static inline int pressed(Ov007Pad *pad, u16 h, int m1, int m2) {
    int ok, n3, n2, n5;
    n3 = 0;
    ok = 1;
    n2 = 0;
    n5 = ((h & m1) == 0) ? ok : n3;
    if (n5 != 0) {
        if (pad->prevKeys & m1) {
            n2 = 1;
        }
    }
    if (n2 != 0) {
        if ((h & m2) == 0) {
            n3 = 1;
        }
    }
    if (n3 == 0) {
        if ((h & m2) || !(pad->prevKeys & m2) || n5 == 0) {
            ok = 0;
        }
    }
    return ok;
}

#pragma opt_propagation off
void func_ov007_020bb4b0(void)
{
    int t1;
    int s;
    Ov007Pad *pad;
    int mat[4];
    u16 h;

    s = (int)SCENE->picker;
    pad = WORK->pad;

    {
        u32 w = pad->heldFrames[9];
        u32 v = pad->heldFrames[8];
        if (v <= w) {
            v = w;
        }
        if (cstd::mod(v, 5) == 1) {
            func_ov007_020bbc08(2, 0xa, 0x1000);
            SCENE->springSet = 0;
        } else {
            h = pad->keys;
            if (pressed(pad, h, 0x200, 0x100)) {
                func_ov007_020bbc08(1, 0, 0);
                SCENE->springSet = 3;
                func_ov007_020bdeb0(0x24);
            }
        }
    }

    {
        u32 lim = pad->heldFrames[6];
        int t2 = pad->heldFrames[1];
        int dir;
        t1 = pad->heldFrames[0];
        if ((u32)t1 <= lim) {
            t1 = lim;
        }
        lim = pad->heldFrames[5];
        if ((u32)t2 <= lim) {
            t2 = lim;
        }
        dir = (t1 > t2) ? 1 : -1;
        if (t1 <= t2) {
            t1 = t2;
        }
        if (t1 > 0) {
            int extra;
            int a;
            int b;
            a = 0x1000;
            extra = 0;
            b = a;
            int ratio, ease, v2, half, fpv;
            SCENE->springSet = 0;
            if (t1 <= 0) {
                ratio = 0;
            } else if (t1 >= 0x64) {
                ratio = 0x1000;
            } else {
                ratio = cstd::div(t1 << 0xc, 0x64);
            }
            ease = (int)(((s64)ratio * (0x2000 - ratio)) >> 0xc);
            if (t1 <= 0x50) {
                v2 = 0;
            } else if (t1 >= 0xc8) {
                v2 = 0x1000;
            } else {
                v2 = cstd::div((t1 - 0x50) << 0xc, 0x78);
            }
            half = ((int)(((s64)v2 * (0x2000 - v2)) >> 0xc)) / 2;
            fpv = half + 0x1000;
            if (t1 >= 0xa0) {
                int m = cstd::mod(t1 - 0xa0, 5);
                int mc, v3, v3sq;
                u32 u;
                s16 tbl;
                if (m <= 0) {
                    mc = 0;
                } else if (m >= 5) {
                    mc = 0x1000;
                } else {
                    mc = cstd::div(m << 0xc, 5);
                }
                if (t1 <= 0xa0) {
                    v3 = 0;
                } else if (t1 >= 0xc8) {
                    v3 = 0x1000;
                } else {
                    v3 = cstd::div((t1 - 0xa0) << 0xc, 0x28);
                }
                v3sq = (int)(((s64)v3 * v3) >> 0xc);
                u = (u32)(mc * 0xffff);
                u = u << 4;
                u = u >> 0x10;
                tbl = data_02082214[((int)u >> 4) * 2];
                extra = FX_MUL(v3sq, (tbl * (s16)0xa));
            }
            if (dir > 0) {
                a -= ease;
                b += extra + FX_MUL(ease, fpv);
            } else {
                a += extra + FX_MUL(ease, fpv);
                b -= ease;
            }
            func_ov007_020c55bc(s, a, b);
            func_ov007_020bde2c(0x38);
        } else {
            h = pad->keys;
            if (pressed(pad, h, 0x40, 0x400) || pressed(pad, h, 0x80, 2)) {
                func_ov007_020bbc08(0, 0, 0);
                SCENE->springSet = 3;
                func_ov007_020bdeb0(0x24);
            }
        }
    }

    {
        int c2;
        int c1;
        int dir2;
        int amp;
        u32 lim2;
        lim2 = pad->heldFrames[4];
        c1 = pad->heldFrames[2];
        c2 = pad->heldFrames[3];
        if ((u32)c1 <= lim2) {
            c1 = lim2;
        }
        lim2 = pad->heldFrames[7];
        if ((u32)c2 <= lim2) {
            c2 = lim2;
        }
        dir2 = (c1 > c2) ? 1 : -1;
        c1 = (c1 > c2) ? c1 : c2;
        if (c1 > 0) {
            int md = cstd::mod(c1, 5);
            if (c1 < 0x64) {
                int r;
                if (c1 <= 0) {
                    r = 0;
                } else if (c1 >= 0x64) {
                    r = 0x1000;
                } else {
                    r = cstd::div(c1 << 0xc, 0x64);
                }
                amp = r / 2;
            } else {
                int v, sq;
                if (c1 <= 0x64) {
                    v = 0;
                } else if (c1 >= 0x12c) {
                    v = 0x1000;
                } else {
                    v = cstd::div((c1 - 0x64) << 0xc, 0xc8);
                }
                sq = (int)(((s64)v * v) >> 0xc);
                amp = sq / 2 + 0x800;
                if (c1 >= 0x12c) {
                    int m2 = cstd::mod(c1, 0x64);
                    int mc2;
                    u32 u2;
                    int t2v;
                    if (m2 <= 0) {
                        mc2 = 0;
                    } else if (m2 >= 0x64) {
                        mc2 = 0x1000;
                    } else {
                        mc2 = cstd::div(m2 << 0xc, 0x64);
                    }
                    u2 = (u32)(mc2 * 0xffff);
                    u2 = u2 << 4;
                    u2 = u2 >> 0x10;
                    t2v = data_02082214[((int)u2 >> 4) * 2];
                    if (t2v < 0) {
                        t2v = -t2v;
                    }
                    amp = FX_MUL((t2v / 4 + 0xc00), amp);
                }
            }
            if (md == 0) {
                u32 uu = (u32)((dir2 * amp) * 0x3555);
                int idx;
                uu = uu << 4;
                uu = uu >> 0x10;
                idx = (int)uu >> 4;
                func_020524e4(mat, data_02082214[idx * 2], data_02082214[idx * 2 + 1]);
                func_ov007_020c5490((char *)s, mat);
            } else {
                int n = cstd::div(((Ov007Picker *)s)->groupCount, 4) + 1;
                if (n == 1) {
                    n = ((Ov007Picker *)s)->groupCount;
                }
                dir2 = (md - 1) * n;
                md = dir2 + n;
                if (md > ((Ov007Picker *)s)->groupCount) {
                    md = ((Ov007Picker *)s)->groupCount;
                }
                for (; dir2 < md; dir2++) {
                    func_ov007_020c6314((char *)SCENE->picker, dir2, 0);
                    func_ov007_020c6174((char *)SCENE->picker, dir2, 1);
                }
            }
            func_ov007_020bda38(amp);
            SCENE->springSet = 2;
        } else {
            h = pad->keys;
            if (pressed(pad, h, 0x10, 1) || pressed(pad, h, 0x20, 0x800)) {
                func_ov007_020bbc08(0, 0, 0);
                SCENE->springSet = 0;
            }
        }
    }
}
}
