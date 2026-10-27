//cpp
#include "types.h"
#include "nitro/fx/fx.h"
#include "Ov007MenuState.h"
#include "cstd.h"

extern "C" {

extern u8 data_ov007_02104ba0[];

/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates; names
 * as in func_ov007_020ba05c and func_ov007_020bb4b0, only the slots this
 * function touches. */
typedef struct Ov007PickerScene {
    void *picker;              /* 0x00: func_ov007_020c690c */
    Ov007MenuState *states[4]; /* 0x04: func_ov007_020c9388; [1] is the main one */
    char pad_14[8];
    /* 0x1c: which six-int row of data_ov007_020d7b80 func_ov007_020ba9bc
     * installs as the picker's springConstants; this function picks 0, 2
     * or 4 */
    int springSet;
} Ov007PickerScene;

typedef char Ov007PickerScene_size_must_be_0x20[sizeof(Ov007PickerScene) == 0x20 ? 1 : -1];

/* The extern keeps the tree's u8[] spelling; the typed view is reached
 * through a cast macro. */
#define SCENE (*(Ov007PickerScene **)data_ov007_02104ba0)
extern u16 data_ov007_020d7b54[];
extern short data_02082214[];

extern void func_ov007_020c92d0(void *a);
extern void func_ov007_020bbc08(int a, int b, int c);
extern void func_ov007_020c55bc(int a, int b, int c);

void func_ov007_020bad8c(void)
{
    Ov007PickerScene *mgr;
    Ov007MenuState *obj;
    int r6;
    int r5;
    u16 period;
    int var_r4;
    int t;
    s16 sw;

    mgr = SCENE;
    r6 = (int)mgr->picker;
    func_ov007_020c92d0(mgr->states[2]);

    obj = SCENE->states[2];
    r5 = obj->stateTicks;
    period = data_ov007_020d7b54[obj->currentState];
    t = cstd::mod(r5, period);
    if (t <= 0) {
        var_r4 = 0;
    } else if (t >= period) {
        var_r4 = 0x1000;
    } else {
        var_r4 = cstd::div(t << 0xc, period);
    }

    mgr = SCENE;
    obj = mgr->states[2];
    sw = obj->currentState;

    switch (sw) {
    case 0:
        if (r5 != 0) {
            return;
        }
        func_ov007_020bbc08(1, 0, 0);
        return;
    case 1:
        mgr->springSet = 0;
        if (cstd::mod(r5, 6) != 0) {
            return;
        }
        {
            int v;
            if (var_r4 >= 0x800) {
                v = 0x1000 - ((var_r4 - 0x800) * 2);
            } else {
                v = var_r4 * 2;
            }
            func_ov007_020bbc08(3, 0xa, (int)(((long long)v * (0x2000 - v)) >> 0xc));
        }
        return;
    case 2:
    {
        int v;
        int amt;
        if (var_r4 >= 0x800) {
            v = 0x1000 - ((var_r4 - 0x800) * 2);
        } else {
            v = var_r4 * 2;
        }
        amt = (int)(((long long)v * (0x2000 - v)) >> 0xc) + 0x1000;
        func_ov007_020c55bc(r6, amt, amt);
        obj = SCENE->states[2];
        if (r5 >= data_ov007_020d7b54[obj->currentState]) {
            obj->requestedState = 0;
        }
        if (var_r4 <= 0x800) {
            SCENE->springSet = 4;
        } else {
            SCENE->springSet = 0;
        }
        return;
    }
    case 3:
    {
        int d;
        u16 p3;
        int m;
        int var_r0;

        d = r5 - 0x14;
        if (d < 0) {
            return;
        }
        if (d > data_ov007_020d7b54[sw] * 3) {
            return;
        }
        p3 = data_ov007_020d7b54[3];
        m = cstd::mod(d, p3);
        if (m <= 0) {
            var_r0 = 0;
        } else if (m >= p3) {
            var_r0 = 0x1000;
        } else {
            var_r0 = cstd::div(m << 0xc, p3);
        }
        {
            u32 u = (u32)(var_r0 * 0xffff);
            int idx;
            short tblval;
            int amt;
            u = u << 4;
            u = u >> 0x10;
            idx = (int)u >> 4;
            tblval = data_02082214[idx * 2];
            amt = FX_MUL(tblval, 0x258);
            func_ov007_020c55bc(r6, amt + 0x1000, 0x1000 - amt);
        }
        SCENE->springSet = 2;
        return;
    }
    case 4:
    {
        int m = cstd::mod(r5, 0x3c);
        SCENE->springSet = 2;
        if (m == 0) {
            func_ov007_020bbc08(1, 0, 0);
            return;
        }
        if (m != 0x1e) {
            return;
        }
        func_ov007_020bbc08(3, 0x1e, FX_MUL(var_r4, 0x7d0) + 0xc8);
        return;
    }
    case 5:
    default:
        return;
    }
}
}
