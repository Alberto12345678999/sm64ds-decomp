#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Work.h"
extern void func_ov007_020bdeb0(int a);
extern char* data_ov007_02103360;
extern char* data_ov007_0210342c;

/* data_ov007_02103360: the 0x1c-byte menu cursor func_ov007_020b30b0
 * allocates. Only the slots this file touches are spelled; +0x18 (-1 at
 * init) is not read here. */
typedef struct Ov007Cursor {
    Ov007MenuState *state; /* 0x00: func_ov007_020c9388(0xff); func_ov007_020b2e64 ticks it */
    void *sprite;          /* 0x04: func_ov007_020c44e4 */
    int mode;              /* 0x08: func_ov007_020b2cf0's name; 2 picks the second move sound */
    /* 0x0c/0x0e: the last move's direction, -1/0/1 per axis;
     * func_ov007_020b2cf0 eases the sprite back from it */
    s16 nudgeX;
    s16 nudgeY;
    /* 0x10, medium confidence: func_ov007_020b2e64 sets it on a fresh confirm
     * press; states 9 and 0xc/0xd here take it as a step and clear it */
    int confirm;
    /* 0x14: func_ov007_020b2e64's key-repeat direction this frame: -1 none,
     * 0 up, 1 down, 2 right, 3 left */
    int dirPressed;
} Ov007Cursor;

/* The externs keep the tree's char * spelling (the declaration-agreement
 * gate); the typed views are reached through cast macros. */
#define CURSOR ((Ov007Cursor *)data_ov007_02103360)
#define WORK ((Ov007Work *)data_ov007_0210342c)

int func_ov007_020b3708(void)
{
    int ip;
    int r3 = 1;
    int r2;
    Ov007MenuState *p;
    int r4;

    p = CURSOR->state;
    r2 = CURSOR->dirPressed;
    ip = p->currentState;
    r4 = p->requestedState;

    switch (ip) {
    case 0xff:
        r3 = 0;
        break;
    case 0:
        if (r2 == 2) r4 = 2;
        else if (r2 == 3) r4 = r3;
        else if (r2 == 0) r4 = 7;
        break;
    case 1:
        if (r2 == 2) r4 = 0;
        else if (r2 == 3) r4 = 2;
        else if (r2 == 0) r4 = 7;
        break;
    case 2:
        if (r2 == 2) r4 = r3;
        else if (r2 == 3) r4 = 0;
        else if (r2 == 0) r4 = 7;
        break;
    case 7:
        if (r2 == 1) {
            r4 = p->previousState;
        }
        break;
    case 8:
        if (r2 == 0) {
            r4 = 0xfd;
        }
        break;
    case 9:
        if (r2 == 1) {
            r4 = 0xfd;
        } else if (r2 == 2 || CURSOR->confirm != 0) {
            r3 = 0;
            CURSOR->confirm = 0;
            r4 = 0xb;
        } else if (r2 == 3) {
            r3 = 0;
            CURSOR->confirm = 0;
            r4 = 0xa;
        }
        break;
    case 0xa:
    case 0xb:
        if (p->stateTicks == 0) {
            CURSOR->confirm = 1;
            r4 = 9;
        }
        break;
    case 0xc:
    case 0xd:
        if (r2 == 0) {
            r4 = 9;
        } else if (r2 == 1) {
            r4 = 8;
        } else if (p->stateTicks == 0 && (u16)(s16)(p->previousState - 0xc) <= 1) {
            CURSOR->confirm = 1;
        } else {
            int t;
            if (r2 == 2 || ((t = CURSOR->confirm) != 0 && ip == 0xc)) {
                p->currentState = 0xc;
                r3 = 0;
                CURSOR->confirm = 0;
                r4 = 0xd;
            } else if (r2 == 3 || (t != 0 && ip == 0xd)) {
                p->currentState = 0xd;
                r3 = 0;
                CURSOR->confirm = 0;
                r4 = 0xc;
            }
        }
        break;
    case 0xe:
        if (r2 == 2) r4 = 0xf;
        else if (r2 == 3) r4 = 0x10;
        else if (r2 == 1) r4 = 0xfe;
        break;
    case 0xf:
        if (r2 == 2) r4 = 0x10;
        else if (r2 == 3) r4 = 0xe;
        else if (r2 == 1) r4 = 0xfe;
        break;
    case 0x10:
        if (r2 == 2) r4 = 0xe;
        else if (r2 == 3) r4 = 0xf;
        else if (r2 == 1) r4 = 0xfe;
        break;
    case 0x11:
        if (r2 == 2) r4 = 0x12;
        else if (r2 == 3) r4 = 0x13;
        else if (r2 == 0) r4 = 0xe;
        else if (r2 == 1) r4 = 0x14;
        break;
    case 0x12:
        if (r2 == 2) r4 = 0x13;
        else if (r2 == 3) r4 = 0x11;
        else if (r2 == 0) r4 = 0xf;
        else if (r2 == 1) r4 = 0x14;
        break;
    case 0x13:
        if (r2 == 2) r4 = 0x11;
        else if (r2 == 3) r4 = 0x12;
        else if (r2 == 0) r4 = 0x10;
        else if (r2 == 1) r4 = 0x14;
        break;
    case 0x14:
        if (r2 == 3 && WORK->states[1]->currentState == 0) {
            r4 = 0x15;
        } else if (r2 == 0) {
            if (WORK->states[1]->currentState == 1) {
                r4 = 0x13;
            } else {
                r4 = p->previousState;
                if ((u16)(s16)(r4 - 0xe) > 2) {
                    r4 = 0x10;
                }
            }
        }
        break;
    case 0x15:
        if (r2 == 0) {
            r4 = p->previousState;
            if ((u16)(s16)(r4 - 0xe) > 2) {
                r4 = 0xf;
            }
        } else if (r2 == 2) {
            r4 = 0x14;
        }
        break;
    case 0x16:
        if (r2 == 2) {
            r4 = 0x17;
        }
        break;
    case 0x17:
        if (r2 == 3) {
            r4 = 0x16;
        }
        break;
    }

    if (r4 != 0xfd) {
        if (r4 == 0xfe) {
            int st = WORK->states[1]->currentState;
            switch (st) {
            case 0:
                r4 = (ip == 0x10) ? 0x14 : 0x15;
                break;
            case 1:
                switch (ip) {
                case 0xe: r4 = 0x11; break;
                case 0xf: r4 = 0x12; break;
                case 0x10: r4 = 0x13; break;
                }
                break;
            default:
                r4 = 0x14;
                break;
            }
        }
    } else {
        u8 b = *(u8 *)(*(char **)WORK->settings + 9);
        r4 = (b != 0) ? 0xc : 0xd;
    }

    if (CURSOR->state->requestedState != r4) {
        if (r2 == 2) {
            CURSOR->nudgeX = 1;
            CURSOR->nudgeY = 0;
        } else if (r2 == 3) {
            CURSOR->nudgeX = -1;
            CURSOR->nudgeY = 0;
        } else if (r2 == 0) {
            CURSOR->nudgeX = 0;
            CURSOR->nudgeY = -1;
        } else if (r2 == 1) {
            CURSOR->nudgeX = 0;
            CURSOR->nudgeY = 1;
        }
        if (r3 != 0) {
            func_ov007_020bdeb0((CURSOR->mode != 2) ? 4 : 5);
        }
    }
    return r4;
}
