/* ov007 manager: proximity/heading gate against the last path node. */
// @symbol func_ov007_020ba05c
/* `dz` is loaded and then subtracted in place; that split is what keeps the two
 * squared distances on the cartridge's sb/sl pair (the whole 9-word residue the
 * earlier drafts carried).
 *
 * Two spellings below are codegen, measured at 2004/b56:
 *  - the scene local `r3` stays char * with view casts; declaring it as
 *    Ov007PickerScene * swaps it from r3 to ip (9 words);
 *  - flags |= 1 stores through ((u32 *)obj)[11] and loads the member; the
 *    member on both sides folds the address into an add (2 words longer). */
#include "Ov007MenuState.h"
#include "Ov007StrokePath.h"
#include "Ov007Touch.h"

/* The 0xd0-byte touch picker func_ov007_020c690c builds. Names follow
 * func_ov007_020c5a6c's own struct; only the slots this file touches. */
typedef struct Ov007Picker {
    char pad_00[8];
    int groupCount; /* 0x08: func_ov007_020c6550 commits the stroke as group
                     * groupCount and counts it; func_ov007_020c6724 clears it */
    char pad_0c[0x14];
    Ov007StrokePath *path; /* 0x20: the stroke being drawn (func_ov007_020c2c68);
                            * func_ov007_020c65bc appends to it */
} Ov007Picker;

/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates. Only
 * the slots this file touches are spelled. */
typedef struct Ov007PickerScene {
    Ov007Picker *picker;       /* 0x00: func_ov007_020c690c */
    Ov007MenuState *states[4]; /* 0x04: func_ov007_020c9388; [1] is the main one */
    char pad_14[0x18];
    int strokeCount; /* 0x2c: picker->groupCount once func_ov007_020c6550 commits a
                      * stroke; cleared with the picker below */
    int awaitingTap; /* 0x30: func_ov007_020b9880 and func_ov007_020ba2e0 set it; the
                      * next fresh press clears it and resets the picker */
    int strokeTime;  /* 0x34: Q12 frames since the stroke began; func_ov007_020c65bc
                      * stores it >> 12 as the new point's progress threshold */
} Ov007PickerScene;

/* data_ov007_0210342c: the overlay's manager; only its touch slot here. */
typedef struct Ov007Work {
    char pad_00[0x50];
    Ov007Touch *touch; /* 0x50: func_ov007_020c2068; updated by func_ov007_020c1db0 */
} Ov007Work;

extern char *data_ov007_02104ba0;
extern char *data_ov007_0210342c;
/* The externs keep the tree's char * spelling (the declaration-agreement
 * gate); the typed views are reached through cast macros. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
#define SCENE ((Ov007PickerScene *)data_ov007_02104ba0)

extern int func_ov007_020c1da0(int i);
extern void func_ov007_020c6724(char *self, int flag);
extern int func_ov007_020c65bc(char *t, int a1, int a2, int a3);
extern void func_ov007_020bdbcc(int a0, int a1);
extern int func_ov007_020c6550(char *c);
extern int func_ov007_020bb09c(void);

int func_ov007_020ba05c(void)
{
    Ov007PickerScene *mgr = SCENE;
    int r6 = 0;
    int r5;
    Ov007Touch *r4 = WORK->touch;

    if (mgr->awaitingTap != 0 && r4->cur.touch != 0 && r4->prev.touch == 0 &&
        r4->releasedFrames >= 1 && func_ov007_020c1da0(0) == 0) {
        SCENE->awaitingTap = 0;
        func_ov007_020c6724((char *)SCENE->picker, 0);
        SCENE->strokeCount = 0;
    }
    {
        Ov007PickerScene *m = SCENE;
        Ov007StrokePath *o = m->picker->path;
        if (o->pointCount == 0)
            m->strokeTime = 0;
        else
            m->strokeTime += 0x1000;
    }
    if (func_ov007_020c1da0(0) == 0) {
        char *r3 = data_ov007_02104ba0;
        int st = ((Ov007PickerScene *)r3)->states[1]->currentState;
        if (st != 6 && st != 7 && ((Ov007PickerScene *)r3)->awaitingTap == 0) {
            if (r4->cur.touch != 0) {
                unsigned int cnt;
                Ov007StrokePath *o;
                int flag;
                int y;
                int x;
                o = ((Ov007PickerScene *)r3)->picker->path;
                r5 = 0;
                flag = 0;
                cnt = o->pointCount;
                y = r4->cur.x;
                x = r4->cur.y;
                if (cnt >= 2) {
                    int idx = cnt - 2;
                    int dz = o->yCoords[idx] >> 12;
                    int rz = r4->deltaY;
                    int dx = (o->xCoords[idx] >> 12) - y;
                    int dd = r4->deltaX * r4->deltaX + rz * rz;
                    int dd2;
                    dz -= x;
                    dd2 = dx * dx + dz * dz;
                    if (dd >= 0x100 && dd2 <= 4)
                        flag = 1;
                }
                if (flag == 0) {
                    r5 = func_ov007_020c65bc((char *)((Ov007PickerScene *)r3)->picker, y, x,
                                             ((Ov007PickerScene *)r3)->strokeTime >> 12);
                    func_ov007_020bdbcc(r4->deltaX, r4->deltaY);
                } else {
                    Ov007Touch *obj = WORK->touch;
                    ((u32 *)obj)[11] = obj->flags | 1;
                }
                if (r5 == 2) {
                    func_ov007_020c6550((char *)SCENE->picker);
                    SCENE->strokeTime = 0;
                    r6 = 1;
                } else if (r5 == 1) {
                    Ov007Touch *obj = WORK->touch;
                    obj->countdown = 0;
                }
            } else if (r4->cur.touch == 0) {
                Ov007Touch *obj = WORK->touch;
                if (obj->releasedFrames == 1) {
                    int res = func_ov007_020c6550((char *)((Ov007PickerScene *)r3)->picker);
                    if (res != 0) {
                        Ov007PickerScene *s;
                        if (res == 2)
                            r6 = 1;
                        s = SCENE;
                        s->strokeCount = s->picker->groupCount;
                        SCENE->strokeTime = 0;
                        obj = WORK->touch;
                        ((u32 *)obj)[11] = obj->flags | 1;
                    }
                }
            }
        }
    }
    func_ov007_020bb09c();
    return r6;
}
