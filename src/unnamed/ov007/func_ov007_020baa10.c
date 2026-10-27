#include "types.h"
// @symbol func_ov007_020baa10
/* recovered: shared common types, declarations from a shared header */
#include "decl_common.h"
/* recovered: shared common types */
#include "common.h"
#include "nitro/fx/fx.h"
#include "Ov007MenuState.h"
extern s16 data_02082214[];

/* The 0xd0-byte touch picker (func_ov007_020c690c); names as in
 * func_ov007_020c684c, only the slots this file touches. */
typedef struct Ov007Picker {
    char pad_00[0x70];
    Vector3 pos;       /* 0x70 */
    Vector3 restPos;   /* 0x7c: func_ov007_020c6af0 snapshots pos here */
    Vector3 posOffset; /* 0x88: func_ov007_020c5188 adds it to pos for one step */
    char pad_94[0x24];
    Vector3 boundsMin; /* 0xb8: func_ov007_020c510c, the clamp rectangle */
    Vector3 boundsMax; /* 0xc4 */
} Ov007Picker;

/* data_ov007_02104ba0: the picker scene func_ov007_020b9880 allocates. */
typedef struct Ov007PickerScene {
    Ov007Picker *picker;       /* 0x00: func_ov007_020c690c */
    Ov007MenuState *states[4]; /* 0x04: func_ov007_020c9388; [1] is the main one */
} Ov007PickerScene;

/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define SCENE ((Ov007PickerScene *)data_ov007_02104ba0)

/* Each menu state drives the picker's per-step offset across the clamp
 * rectangle; state 5 puts pos back at its rest position. */
void func_ov007_020baa10(void)
{
    Ov007Picker *a;
    s16 state;
    int dx;
    int dy;
    int s;
    Ov007MenuState *menu;
    int counter;

    a = SCENE->picker;
    menu = SCENE->states[3];
    dx = a->boundsMax.x - a->boundsMin.x;
    dy = a->boundsMax.y - a->boundsMin.y;
    func_ov007_020c92d0((char *)menu);
    menu = SCENE->states[3];
    state = menu->currentState;
    counter = menu->stateTicks;

    switch (state) {
    case 0:
        if (counter == 0) {
            a->posOffset.y = 0;
            a->posOffset.x = a->posOffset.y;
        }
        return;
    case 1:
    case 2: {
        int v;
        int m = mod(counter, 0x3c);
        if (m <= 0)
            v = 0;
        else if (m >= 0x3c)
            v = 0x1000;
        else
            v = div(m << 12, 0x3c);
        s = data_02082214[((u16)((v * 0xffff) >> 12) >> 4) * 2];
        if (state == 2) {
            a->posOffset.x = -dx / 48 + func_ov007_020c3ba8(dx / 48 - -dx / 48);
            a->posOffset.y = FX_MUL(s, (dy / 2 - dy / 8));
        } else if (state == 1) {
            a->posOffset.x = FX_MUL(s, (dx / 3));
            a->posOffset.y = -dy / 32 + func_ov007_020c3ba8(dy / 32 - -dy / 32);
        }
        return;
    }
    case 3:
    case 4: {
        int v;
        int idx;
        int m = mod(counter, 0x3c);
        if (m <= 0)
            v = 0;
        else if (m >= 0x3c)
            v = 0x1000;
        else
            v = div(m << 12, 0x3c);
        if (SCENE->states[3]->currentState == 4)
            v = 0x1000 - v;
        idx = ((u16)((v * 0xffff) >> 12) >> 4) * 2;
        a->posOffset.x = FX_MUL((dx / 4), data_02082214[idx + 1]);
        a->posOffset.y = FX_MUL((dy / 4), data_02082214[idx]);
        return;
    }
    case 5:
        if (counter == 0) {
            a->pos = a->restPos;
            a->posOffset.y = 0;
            a->posOffset.x = a->posOffset.y;
        }
        return;
    case 6:
        if (counter == 0) {
            int t;
            t = -dx / 2 + func_ov007_020c3ba8(dx / 2 - -dx / 2);
            a->pos.x = FX_MUL(t, 0x5dcLL);
            t = -dy / 2 + func_ov007_020c3ba8(dy / 2 - -dy / 2);
            a->pos.y = FX_MUL(t, 0x5dcLL);
            a->posOffset.y = 0;
            a->posOffset.x = a->posOffset.y;
        }
        return;
    }
}
