/* func_ov007_020b91b4 at 0x020b91b4 (ov007), size 0x48c
 * Compiler mwccarm 1.2/sp2p3, flags:
 * -O4,p -enum int -lang c99 -char signed -interworking -proc arm946e -gccext,on -msgstyle gcc
 * 0/1 select is emitted true-arm-first and {0,1} int arms canonicalize to bool(!=0);
 * pointer-typed arms ((char*)0/(char*)1 cast back to int) pin moveq-first */
#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Sprite.h"
#include "Ov007Touch.h"

/* The 0xd0-byte touch picker func_ov007_020c690c builds; names as in
 * func_ov007_020c5014 and func_ov007_020c684c, only the slots this file
 * touches. */
typedef struct Ov007Picker {
    char pad_00[8];
    int groupCount; /* 0x08: committed strokes */
    char pad_0c[0xa0];
    /* 0xac/0xb0: the draw limit; func_ov007_020c4dfc draws whole groups up
     * to limitGroup and that group's first limitIndex points */
    int limitGroup;
    int limitIndex;
} Ov007Picker;

/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates; names
 * as in that file, func_ov007_020ba05c and func_ov007_020bb09c, only the
 * slots this file touches. */
typedef struct Ov007PickerScene {
    Ov007Picker *picker;       /* 0x00: func_ov007_020c690c */
    Ov007MenuState *states[4]; /* 0x04: func_ov007_020c9388; [1] is the main one */
    /* 0x14: func_ov007_020c5db0's point total over the stroke and every
     * group; func_ov007_020ba368 divides the drawn progress by it */
    int totalPoints;
    /* 0x18, medium confidence: func_ov007_020c5d5c's sum of each group's
     * last progressThresholds entry (strokeTime >> 12 when the point was
     * added); nothing reads it back in the files seen */
    int totalStrokeTime;
    char pad_1c[0x14];
    int awaitingTap; /* 0x30: func_ov007_020ba05c clears it on the next fresh press */
    int strokeTime;  /* 0x34: Q12 frames since the stroke began */
    char pad_38[4];
    s32 tweenOut[2];              /* 0x3c: bound as tweens[i]->out */
    struct Ov007Tween *tweens[2]; /* 0x44: func_ov007_020c908c */
} Ov007PickerScene;

/* data_ov007_02104b9c: the 0x14 record of the scene's sprites
 * (func_ov007_020b9880). */
typedef struct Ov007PickerSprites {
    /* 0x00, medium confidence: Q12; while it is <= 0x1000,
     * func_ov007_020b8fd4 offsets sprites[1] by (0x1000 - it) << 8 in the
     * direction of the scene's +0x20 mode; func_ov007_020ba368 eases it up */
    s32 slideProgress;
    Ov007Sprite *sprites[4]; /* 0x04: func_ov007_020c44e4 */
} Ov007PickerSprites;

/* data_ov007_0210342c: the overlay's manager; only the slot this file reads. */
typedef struct Ov007Work {
    char pad_00[0x50];
    Ov007Touch *touch; /* 0x50: func_ov007_020c2068 */
} Ov007Work;

typedef char Ov007Picker_limitIndex_must_end_at_0xb4[sizeof(Ov007Picker) == 0xb4 ? 1 : -1];
typedef char Ov007PickerScene_size_must_be_0x4c[sizeof(Ov007PickerScene) == 0x4c ? 1 : -1];

extern char *data_ov007_02104ba0;
extern char *data_ov007_02104b9c;
extern char *data_ov007_0210342c;
/* The externs keep the tree's char * spelling (the declaration-agreement
 * gate); the typed views are reached through cast macros. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
#define SCENE ((Ov007PickerScene *)data_ov007_02104ba0)
#define SPRITES ((Ov007PickerSprites *)data_ov007_02104b9c)
extern void func_ov007_020c92d0(void *p);
extern int func_ov007_020c8f98(void *p);
extern int func_ov007_020c5db0(void *p);
extern int func_ov007_020c3be0(int t, int a, int b);
extern int func_ov007_020c5d5c(void *o);
extern int func_ov007_020bbd24(int a);
extern void func_ov007_020c4dfc(void *c, int a1, int a2, int a3);
extern int _ZN4cstd3divEii(int a, int b);
extern void func_ov007_020c4f50(void *c, int a1, int a2, int a3, int a4);
extern void func_ov007_020c4e98(void *c, int a1, int a2, int a3, int a4, int a5, int a6);
void func_ov007_020b91b4(void)
{
  int r7;
  Ov007Picker *r6;
  int r5;
  long long new_var;
  int r4;
  short st;
  int t;
  r6 = SCENE->picker;
  func_ov007_020c92d0(SCENE->states[1]);
  r4 = SCENE->states[1]->stateTicks;
  func_ov007_020c8f98(SCENE->tweens[0]);
  func_ov007_020c8f98(SCENE->tweens[1]);
  SCENE->totalPoints = func_ov007_020c5db0(SCENE->picker);
  r5 = func_ov007_020c3be0(SCENE->tweenOut[1], 0, 0x59e8);
  t = SCENE->tweenOut[0];
  if (t >= 0x1000)
  {
    r7 = 0x200;
  }
  else
    if (t <= 0)
  {
    r7 = 0xc0;
  }
  else
  {
    r7 = (int) (((((long long) (0x1000 - t)) * 0xc0) + (new_var = ((long long) t) << 9)) >> 0xc);
  }
  st = SCENE->states[1]->currentState;
  switch (st)
  {
    case 0:

        do {
        case 1:
            if ((SCENE->states[1]->stateTicks) == 0) {
                Ov007Picker *a0 = SCENE->picker;
                a0->limitGroup = 0;
                a0->limitIndex = 0;
                SCENE->strokeTime = 0;
                SCENE->totalStrokeTime = func_ov007_020c5d5c(SCENE->picker);
                SPRITES->slideProgress = 0;
            }
            {
                int b = func_ov007_020bbd24(
                    (int)(((SCENE->states[1]->currentState) == 0) ? ((char *)0) : ((char *)1)));
                func_ov007_020c4dfc(r6, r7, r5, 0x1f);
                if (b == 0) {
                    return;
                }
            }
            SCENE->awaitingTap = 0;
            SCENE->states[1]->requestedState = 8;
            return;
        case 2:
            if (r4 == 0) {
                SPRITES->sprites[0]->alpha = 0;
                SPRITES->sprites[1]->alpha = 0;
                SPRITES->slideProgress = 0x1000;
            }
            {
                int q;
                if (r4 <= 0) {
                    q = 0;
                } else if (r4 >= 0x28) {
                    q = 0x1000;
                } else {
                    q = _ZN4cstd3divEii(r4 << 0xc, 0x28);
                }
                SPRITES->sprites[1]->alpha = q * 0xc;
                if (q < 0x1000) {
                    return;
                }
            }
            SCENE->states[1]->requestedState = 5;
            return;
        case 3:
        case 4:
        case 5: {
            int *p = &SPRITES->sprites[1]->alpha;
            if (st == 4) {
                *p += 0x1000;
                if ((*p) >= 0x1f000) {
                    *p = 0x1f000;
                    SPRITES->sprites[0]->alpha = 0x1f000;
                    SCENE->states[1]->requestedState = 5;
                }
            } else if (st == 3) {
                if (r4 == 0) {
                    SPRITES->sprites[0]->alpha = 0;
                }
                *p -= 0x1000;
                if ((*p) <= 0xc000) {
                    *p = 0xc000;
                    SCENE->states[1]->requestedState = 5;
                }
            }
        }
            if ((SCENE->awaitingTap) != 0) {
                return;
            }
            func_ov007_020c4f50(r6, r7, r5, 0x1f, 1);
            return;
        case 6:
        case 7: {
            int r8v;
            int sb;
            int q;
            if (st == 6) {
                r8v = r6->groupCount;
            } else {
                r8v = (r6->groupCount) - 1;
            }
            if (r4 <= 0) {
                q = 0;
            } else if (r4 >= 0xf) {
                q = 0x1000;
            } else {
                q = _ZN4cstd3divEii(r4 << 0xc, 0xf);
            }
            if ((SCENE->states[1]->currentState) == 6) {
                q = 0x1000 - q;
            }
            sb = (q * 0x1f) >> 0xc;
            if (sb <= 0) {
                sb = 1;
            }
            func_ov007_020c4e98(r6, r7, r5, 0x1f, r8v, func_ov007_020c3be0(q, 0x18df, r5), sb);
            if (r4 < 0xf) {
                return;
            }
        }
            SCENE->states[1]->requestedState = 5;
            {
                Ov007Touch *o = WORK->touch;
                /* the read through a const view is load-bearing: `o->flags |= 1`
                 * builds 4 bytes longer */
                o->flags = ((const Ov007Touch *)o)->flags | 1;
            }
            return;
        } while (0);
    case 8:
        if ((SCENE->awaitingTap) != 0) {
            SCENE->states[1]->requestedState = 1;
            return;
        }
      func_ov007_020c4f50(r6, r7, r5, 0x1f, 1);
      return;

  }

}
