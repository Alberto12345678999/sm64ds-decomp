//cpp
#include "cstd.h"
#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Work.h"

/* func_ov007_020c946c's 0x44-byte palette buffer: func_ov007_020c940c
 * copies 0x40 bytes of colours from source into colors, or clears them when
 * source is 0. func_ov007_020b69c4 sources buffer 0 from buffer 2's colours
 * and buffer 1 from buffer 0's. */
struct Ov007PaletteBuf {
    const void *source; /* 0x00 */
    u16 colors[0x20];   /* 0x04 */
};

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
/* Ov007Work types paletteBufs as void *. */
#define PALETTE_BUF(i) ((Ov007PaletteBuf *)WORK->paletteBufs[i])

/* 32-colour palettes, 0x40 bytes each */
extern char data_ov007_02102f28[];

extern "C" {
extern void func_ov007_020c92d0(char *record);
extern void func_ov007_020c940c(void *buf);
extern void func_ov007_020c93c4(int t, void *from, void *to, void *out);
}

/* Fades the menu palette to palette n over `frames` frames: on entry it
 * loads n into buffer 2, and snapshots the shown colours (buffer 0) into
 * buffer 1, or with frames 0 copies n straight into buffer 0. While the
 * fade runs buffer 0 is blended from 1 to 2 and the state's stateWork is
 * 1. */
extern "C" void func_ov007_020bce70(short n, int frames) {
    int t;

    WORK->paletteState->requestedState = n;
    func_ov007_020c92d0((char *)WORK->paletteState);

    t = WORK->paletteState->stateTicks;
    if (t == 0) {
        PALETTE_BUF(2)->source = data_ov007_02102f28 + (n << 6);
        func_ov007_020c940c(PALETTE_BUF(2));
        if (frames == 0) {
            t = frames + 1;
            func_ov007_020c940c(PALETTE_BUF(0));
        } else {
            func_ov007_020c940c(PALETTE_BUF(1));
        }
    }

    if (t >= 0 && t <= frames) {
        int ratio;
        if (t <= 0)
            ratio = 0;
        else if (t >= frames)
            ratio = 0x1000;
        else
            ratio = cstd::div(t << 12, frames);
        func_ov007_020c93c4(ratio, PALETTE_BUF(1), PALETTE_BUF(2), PALETTE_BUF(0));
        WORK->paletteState->stateWork = 1;
    } else {
        if (WORK->paletteState->stateWork != 0)
            WORK->paletteState->stateWork = 0;
    }
}
