#include "Ov007MenuState.h"
#include "Ov007Tween.h"

#include "Ov007Sprite.h"
#include "Ov007StrokePath.h"
#include "Ov007Touch.h"

extern int func_ov007_020bdeb0(int a);
extern int func_ov007_020c1da0(int i);

extern char* data_ov007_0210342c;
extern char* data_ov007_02104ba0;
extern char* data_ov007_02104b9c;

/* The 0xd0-byte touch picker (func_ov007_020c690c); names as in
 * func_ov007_020ba05c and func_ov007_020c690c, only the slots read here. */
typedef struct Ov007Picker {
    char pad_00[8];
    int groupCount; /* 0x08: committed strokes; undo/redo below step it */
    char pad_0c[8];
    /* 0x14, medium confidence: func_ov007_020c6784 seeds it with
     * func_ov007_020c5db0's point total over the stroke and every group;
     * undo/redo below take a group's +0xa out or put it back */
    int totalPoints;
    char pad_18[0x20];
    Ov007StrokePath **groups; /* 0x38: committed strokes (func_ov007_020c6d20) */
} Ov007Picker;

/* data_ov007_02104ba0: the scene func_ov007_020b9880 allocates; names as in
 * that file and func_ov007_020ba05c. */
typedef struct Ov007PickerScene {
    Ov007Picker *picker;       /* 0x00: func_ov007_020c690c */
    Ov007MenuState *states[4]; /* 0x04: func_ov007_020c9388; [1] is the main one */
    char pad_14[0x18];
    int strokeCount;       /* 0x2c: redo stops at it */
    int awaitingTap;       /* 0x30 */
    char pad_34[8];
    s32 tweenOut[2];       /* 0x3c: bound as tweens[i]->out */
    Ov007Tween *tweens[2]; /* 0x44: func_ov007_020c908c */
} Ov007PickerScene;

/* data_ov007_02104b9c: the scene's sprites (func_ov007_020b9880). */
typedef struct Ov007PickerSprites {
    char pad_00[4];
    Ov007Sprite *sprites[4]; /* 0x04: func_ov007_020c44e4 */
} Ov007PickerSprites;

/* The 0x70-byte key record func_ov007_020c2304 allocates (names as in
 * func_ov007_020b1cf0). */
typedef struct Ov007Pad {
    u16 keys;     /* 0x00: held this frame */
    u16 prevKeys; /* 0x02: held last frame */
} Ov007Pad;

/* data_ov007_0210342c: the overlay's manager; only its input slots here. */
typedef struct Ov007Work {
    char pad_00[0x50];
    Ov007Touch *touch; /* 0x50: func_ov007_020c2068 */
    Ov007Pad *pad;     /* 0x54: func_ov007_020c2304 */
} Ov007Work;

/* The externs keep the tree's char * spelling (the declaration-agreement
 * gate); the typed views are reached through cast macros. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
#define SCENE ((Ov007PickerScene *)data_ov007_02104ba0)
#define SCENE_SPRITES ((Ov007PickerSprites *)data_ov007_02104b9c)

/* The scene's key handling (fresh presses, keys & ~prevKeys): X/up and
 * B/down step tweens[0] between its three stops, R/L request menu state 3 or
 * 4 by sprites[1]'s alpha, and Y/left and A/right undo or redo the last
 * committed stroke. */
int func_ov007_020bb09c(void)
{
    Ov007Picker *r5 = SCENE->picker;
    Ov007Pad *r4 = WORK->pad;
    unsigned short r2 = r4->keys;
    int r3 = 0;

    if ((r2 & 0x400) && !(r4->prevKeys & 0x400)) {
        r3 = 1;
    }
    if (r3 != 0 || ((r2 & 0x40) && !(r4->prevKeys & 0x40))) {
        int r1;
        int ip;
        Ov007Tween *r3p = SCENE->tweens[0];
        r1 = r3p->to;
        switch (r1) {
        case 0:      ip = 0x800; break;
        case 0x800:  ip = 0x1000; break;
        case 0x1000: ip = -1; break;
        default:     ip = 0; break;
        }
        if (ip != -1) {
            int t = SCENE->tweenOut[0];
            r3p->state = 1;
            r3p->mode = 1;
            r3p->t = 0;
            r3p->step = 0x100;
            r3p->from = t;
            *r3p->out = r3p->from;
            r3p->to = ip;
            func_ov007_020bdeb0(0x23);
        }
    } else if (((r2 & 2) && !(r4->prevKeys & 2)) ||
               ((r2 & 0x80) && !(r4->prevKeys & 0x80))) {
        int r1;
        int ip;
        Ov007Tween *r3p = SCENE->tweens[0];
        r1 = r3p->to;
        switch (r1) {
        case 0:      ip = -1; break;
        case 0x800:  ip = 0; break;
        case 0x1000: ip = 0x800; break;
        default:     ip = 0; break;
        }
        if (ip != -1) {
            int t = SCENE->tweenOut[0];
            r3p->state = 1;
            r3p->mode = 1;
            r3p->t = 0;
            r3p->step = 0x100;
            r3p->from = t;
            *r3p->out = r3p->from;
            r3p->to = ip;
            func_ov007_020bdeb0(0x22);
        }
    }

    {
        int r3b = 0;
        Ov007Pad *r2p = WORK->pad;
        unsigned short r1 = r2p->keys;
        if ((r1 & 0x100) && !(r2p->prevKeys & 0x100)) {
            r3b = 1;
        }
        if (r3b != 0 || ((r1 & 0x200) && !(r2p->prevKeys & 0x200))) {
            if (SCENE_SPRITES->sprites[1]->alpha == 0x1f000) {
                SCENE->states[1]->requestedState = 3;
                func_ov007_020bdeb0(0x29);
            } else {
                SCENE->states[1]->requestedState = 4;
                func_ov007_020bdeb0(0x2a);
            }
        }
    }

    {
        Ov007Touch *r1 = WORK->touch;
        if (r1->cur.touch != 0) {
            return r1->cur.touch;
        }
        if (r1->releasedFrames < 1U) {
            return r1->releasedFrames;
        }
    }

    {
        int rv = func_ov007_020c1da0(0);
        if (rv != 0) {
            return rv;
        }
    }

    {
        Ov007PickerScene *b = *(Ov007PickerScene *volatile *)&data_ov007_02104ba0;
        short st = b->states[1]->currentState;
        if (st == 6) return st;
        if (st == 7) return st;
        if (b->awaitingTap != 0) {
            return b->awaitingTap;
        }
    }

    {
        unsigned short r1 = r4->keys;
        int r2b = 0;
        if ((r1 & 0x800) && !(r4->prevKeys & 0x800)) {
            r2b = 1;
        }
        if (r2b != 0 || ((r1 & 0x20) && !(r4->prevKeys & 0x20))) {
            int n = r5->groupCount;
            if (n <= 0) return n;
            {
                Ov007StrokePath *e = r5->groups[n - 1];
                int* p14 = &r5->totalPoints;
                int* p8 = &r5->groupCount;
                *p14 = *p14 - e->capacity;
                *p8 = *p8 - 1;
                SCENE->states[1]->requestedState = 6;
                return func_ov007_020bdeb0(0x20);
            }
        }
        if ((r1 & 1) && !(r4->prevKeys & 1)) {
            /* fallthrough to block_66 */
        } else {
            if (!(r1 & 0x10)) return r1 & 0x10;
            if (r4->prevKeys & 0x10) return r4->prevKeys & 0x10;
        }
    }

    {
        Ov007PickerScene *b = *(Ov007PickerScene *volatile *)&data_ov007_02104ba0;
        int n = r5->groupCount;
        int lim = b->strokeCount;
        if (n >= lim) return lim;
        {
            Ov007StrokePath *e = r5->groups[n];
            int* p14 = &r5->totalPoints;
            int* p8 = &r5->groupCount;
            *p14 = *p14 + e->capacity;
            *p8 = *p8 + 1;
            (*(Ov007PickerScene *volatile *)&data_ov007_02104ba0)->states[1]->requestedState = 7;
            return func_ov007_020bdeb0(0x21);
        }
    }
}
