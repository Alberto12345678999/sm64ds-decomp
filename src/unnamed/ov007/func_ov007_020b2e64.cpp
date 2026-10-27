//cpp
#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Work.h"
#include "cstd.h"

extern "C" {

extern int* data_ov007_02103360;
extern int* data_ov007_0210342c;
extern int data_ov007_02103364;
extern int func_ov007_020c1da0(int i);
extern void func_ov007_020c92d0(int q);
extern int func_ov007_020b3360(void);
extern void func_ov007_020b3e84(short* r0);
extern int func_ov007_020b3190(void);

/* data_ov007_02103360: the 0x1c-byte menu cursor func_ov007_020b30b0
 * allocates; names as in func_ov007_020b3708, only the slots this file
 * touches. */
typedef struct Ov007Cursor {
    Ov007MenuState *state; /* 0x00: func_ov007_020c9388(0xff); ticked here */
    char pad_04[0xc];
    int confirm;    /* 0x10: set here on a fresh A or START press; medium confidence */
    int dirPressed; /* 0x14: this frame's key-repeat direction, -1 none, 0 up .. 3 left */
} Ov007Cursor;

/* The 0x70-byte key record func_ov007_020c2304 allocates (names as in
 * func_ov007_020b1cf0). func_ov007_020c20b8 keeps one counter per button,
 * in the order up, down, right, left, A, B, X, Y, L, R, START, SELECT. */
typedef struct Ov007Pad {
    u16 keys;     /* 0x00: held this frame */
    u16 prevKeys; /* 0x02: held last frame */
    /* 0x04: frames each button has been held, 1 on the press frame; 0 while
     * it is up (func_ov007_020c20b8) */
    u32 heldFrames[12];
} Ov007Pad;

typedef char Ov007Cursor_size_must_be_0x18[sizeof(Ov007Cursor) == 0x18 ? 1 : -1];
typedef char Ov007Pad_size_must_be_0x34[sizeof(Ov007Pad) == 0x34 ? 1 : -1];

/* The externs keep the tree's int * spelling (the declaration-agreement
 * gate); the typed views are reached through cast macros. */
#define CURSOR ((Ov007Cursor *)data_ov007_02103360)
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Reads the d-pad into dirPressed with key repeat (the press frame, then
 * every 10 frames from frame 20) and a fresh A or START press into confirm,
 * ticks the cursor state, and runs the cursor (func_ov007_020b3360) unless
 * it is in state 0xff; a confirm also flips data_ov007_02103364 and calls
 * func_ov007_020b3e84. */
void func_ov007_020b2e64(char* self)
{
    unsigned int* r4;
    int r2;
    int r4v;

    CURSOR->confirm = 0;
    r4 = WORK->pad->heldFrames;

    if (func_ov007_020c1da0(0) != 0) {
        r2 = -1;
    } else if (r4[0] == 1 || (r4[0] >= 0x14 && cstd::mod(r4[0] - 0x14, 0xa) == 0)) {
        r2 = 0;
    } else if (r4[1] == 1 || (r4[1] >= 0x14 && cstd::mod(r4[1] - 0x14, 0xa) == 0)) {
        r2 = 1;
    } else if (r4[2] == 1 || (r4[2] >= 0x14 && cstd::mod(r4[2] - 0x14, 0xa) == 0)) {
        r2 = 2;
    } else if (r4[3] == 1 || (r4[3] >= 0x14 && cstd::mod(r4[3] - 0x14, 0xa) == 0)) {
        r2 = 3;
    } else {
        r2 = -1;
    }

    CURSOR->dirPressed = r2;

    r4v = 0;
    if (func_ov007_020c1da0(0) == 0) {
        Ov007Pad *p = WORK->pad;
        int flag = 1;
        if (p->heldFrames[4] != 1) {
            if (p->heldFrames[10] != 1)
                flag = r4v;
        }
        if (flag != 0) r4v = 1;
    }
    CURSOR->confirm = r4v;
    func_ov007_020c92d0((int)CURSOR->state);

    if (CURSOR->state->currentState != 0xff) {
        func_ov007_020b3360();
        if (CURSOR->confirm == 0) {
            return;
        }
        data_ov007_02103364 = (data_ov007_02103364 == 0) ? 1 : 0;
        func_ov007_020b3e84((short*)self);
        return;
    }

    func_ov007_020b3190();
}
}
