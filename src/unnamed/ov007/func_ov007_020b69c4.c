#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007Work.h"

/* func_ov007_020c946c's 0x44-byte palette buffer: func_ov007_020c940c
 * copies 0x40 bytes of colours from source into colors, or clears them when
 * source is 0. */
typedef struct Ov007PaletteBuf {
    const void *source; /* 0x00 */
    u16 colors[0x20];   /* 0x04 */
} Ov007PaletteBuf;

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)
/* Ov007Work types paletteBufs as void *. */
#define PALETTE_BUF(i) ((Ov007PaletteBuf *)WORK->paletteBufs[i])

extern void *func_ov007_020c9388(int initialState);
extern void *func_ov007_020c946c(void *r5);

/* Resets the figure slots and the per-figure stroke stages, then builds the
 * palette state and the three palette buffers: buffer 0 reloads from buffer
 * 2's colours and buffer 1 from buffer 0's. */
void func_ov007_020b69c4(void) {
    int i;

    WORK->model = 0;
    WORK->figure = 0;
    WORK->altFigure = 0;
    WORK->figureIndex = WORK->nextFigureIndex = 0;

    for (i = 0; i < 2; i++) {
        WORK->strokeStage[i] = 0;
    }

    WORK->paletteState = (Ov007MenuState *)func_ov007_020c9388(0);

    for (i = 0; i < 3; i++) {
        WORK->paletteBufs[i] = func_ov007_020c946c(0);
    }

    PALETTE_BUF(0)->source = PALETTE_BUF(2)->colors;
    PALETTE_BUF(1)->source = PALETTE_BUF(0)->colors;
}
