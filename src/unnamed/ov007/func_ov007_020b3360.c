#include "types.h"
#include "Ov007MenuState.h"
extern void func_ov007_020b3c54(void);
extern int func_ov007_020b3708(void);
extern void func_ov007_020c2090(char* c);
extern void func_ov007_020bdeb0(int a);

extern char* data_ov007_02103360;
extern char* data_ov007_0210342c;

/* data_ov007_02103360: the 0x1c-byte menu cursor func_ov007_020b30b0
 * allocates; names as in func_ov007_020b3708, only the slots this file
 * touches. */
typedef struct Ov007Cursor {
    Ov007MenuState *state; /* 0x00: func_ov007_020c9388(0xff) */
    char pad_04[8];
    s16 nudgeX; /* 0x0c: the last move's direction, -1/0/1 per axis */
    s16 nudgeY; /* 0x0e */
    char pad_10[8];
    /* 0x18: the state to come back to: this file saves the current state
     * while it is one of the 0xe..0x10 row and before the jump to 0x17, and
     * requests it again on leaving 0x16/0x17; func_ov007_020b30b0 seeds -1 */
    int returnState;
} Ov007Cursor;

/* The 0x70-byte pad record func_ov007_020c2304 allocates; only the slot this
 * file touches. */
typedef struct Ov007Pad {
    char pad_00[0x64];
    /* 0x64: bit 0 makes func_ov007_020c20b8 read no keys until every key is
     * released, then clears it */
    int inputLock;
} Ov007Pad;

/* The 0x2c-byte item func_ov007_020aea6c allocates and the 0x1c-byte view
 * func_ov007_020b4c04 returns (names as in func_ov007_020beeb0). */
typedef struct Ov007Item {
    char pad_00[4];
    Ov007MenuState *state; /* 0x04: func_ov007_020c9388(1) */
} Ov007Item;

typedef struct Ov007ItemView {
    Ov007Item *item; /* 0x00 */
} Ov007ItemView;

/* data_ov007_0210342c: the overlay's manager; names as in
 * func_ov007_020b1cf0, only the slots this file reads. */
typedef struct Ov007Work {
    char pad_00[4];
    Ov007MenuState *states[3]; /* 0x04: func_ov007_020c9388 */
    char pad_10[0x44];
    Ov007Pad *pad; /* 0x54: func_ov007_020c2304 */
    char pad_58[0xbc];
    Ov007ItemView *itemViews[0x18]; /* 0x114: func_ov007_020b693c, one per func_ov007_020b4c04 */
} Ov007Work;

/* The externs keep the tree's char * spelling (the declaration-agreement
 * gate); the typed views are reached through cast macros. */
#define CURSOR ((Ov007Cursor *)data_ov007_02103360)
#define WORK ((Ov007Work *)data_ov007_0210342c)

void func_ov007_020b3360(void)
{
    Ov007MenuState *p0 = CURSOR->state;

    if (p0->stateTicks == 0) {
        if (p0->previousState == 0xff) {
            CURSOR->nudgeX = 0;
            CURSOR->nudgeY = 1;
        }
        func_ov007_020b3c54();
    }

    {
        int state1 = WORK->states[0]->currentState;

        switch (state1) {
        case 0: {
            Ov007MenuState *s2 = WORK->states[1];
            int state2 = s2->currentState;
            switch (state2) {
            case 0:
                if (s2->requestedState == -1)
                    CURSOR->state->requestedState = func_ov007_020b3708();
                else
                    CURSOR->state->requestedState = 0xff;
                break;
            case 8:
                if (s2->stateTicks <= 1) {
                    {
                        Ov007Pad *o = WORK->pad;
                        /* the const re-read is codegen: `|= 1` is 4 bytes longer */
                        o->inputLock = *(const int *)&o->inputLock | 1;
                    }
                    func_ov007_020c2090((char *)WORK->pad);
                }
                if (WORK->states[1]->requestedState == -1)
                    CURSOR->state->requestedState = func_ov007_020b3708();
                else
                    CURSOR->state->requestedState = 0xff;
                break;
            default:
                CURSOR->state->requestedState = 0xff;
                break;
            }
            break;
        }
        case 5: {
            Ov007MenuState *s2 = WORK->states[1];
            if (s2->stateTicks == 0) {
                int state3 = s2->currentState;
                switch (state3) {
                case 0: {
                    Ov007MenuState *p = CURSOR->state;
                    int cur = p->currentState;
                    if ((u16)(s16)(cur - 0x11) <= 2)
                        p->requestedState = 0x15;
                    break;
                }
                case 1: {
                    Ov007MenuState *p = CURSOR->state;
                    if (p->currentState == 0x15)
                        p->requestedState = 0x11;
                    break;
                }
                case 3:
                case 7:
                case 9: {
                    Ov007MenuState *p = CURSOR->state;
                    int cur = p->currentState;
                    if ((u16)(s16)(cur - 0x11) <= 2)
                        p->requestedState = 0xe;
                    break;
                }
                case 0xb:
                case 0xc:
                    CURSOR->state->requestedState = 0xff;
                    return;
                default:
                    break;
                }
            }

            {
                int a;
                int b;
                Ov007MenuState *p;
                int cur;
                CURSOR->state->requestedState = func_ov007_020b3708();
                p = CURSOR->state;
                cur = p->currentState;
                a = 1;
                if (cur != 0x16 && cur != 0x17)
                    a = 0;
                b = (WORK->itemViews[0x16]->item->state->currentState == 0);
                if (a == 0 && b != 0) {
                    p->requestedState = 0x17;
                    if (CURSOR->state->currentState == 0xff)
                        func_ov007_020bdeb0(3);
                    CURSOR->returnState = CURSOR->state->currentState;
                    CURSOR->nudgeX = 1;
                    CURSOR->nudgeY = 0;
                } else if (a != 0 && b == 0) {
                    int old = CURSOR->returnState;
                    CURSOR->returnState = -1;
                    CURSOR->state->requestedState = old;
                    CURSOR->nudgeX = 0;
                    CURSOR->nudgeY = 1;
                }
            }
            break;
        }
        default:
            CURSOR->state->requestedState = 0xff;
            break;
        }
    }

    {
        Ov007MenuState *p = CURSOR->state;
        int cur = p->currentState;
        if ((u16)(s16)(cur - 0xe) <= 2)
            CURSOR->returnState = cur;
    }
}
