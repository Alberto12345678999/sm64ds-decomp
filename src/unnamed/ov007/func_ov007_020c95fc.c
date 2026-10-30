#include "types.h"
#include "Ov007BgLayer.h"

/* Block 0 of a screen file: a 16-byte header, then the screen data. The
 * whole header is copied before the two sizes are read. */
typedef struct Ov007ScreenBlock {
    int width;  /* 0x00: in tiles; becomes the BG layer's width */
    int height; /* 0x04: in tiles */
    int w8;
    int wc;
} Ov007ScreenBlock;

/* The 0x84-byte block index func_ov007_020c9a2c fills; names as there,
 * untyped: only block 0's data is read. The tag keeps this file's spelling
 * of func_ov007_020c9a2c's parameter. */
typedef struct Ctx {
    void *header;        /* 0x00 */
    void *blocks[16];    /* 0x04 */
    void *blockData[16]; /* 0x44 */
} Ctx;

typedef char Ctx_size_must_be_0x84[sizeof(Ctx) == 0x84 ? 1 : -1];

extern Ov007BgLayer *func_ov007_020c0aa8(void *screen, int bg, int priority, u16 width, u16 height);
extern void func_ov007_020c9a2c(Ctx *ctx, void *a);

/* Builds a BG layer around file a's screen (a blank 0x20 x 0x18-tile layer
 * when there is no file). */
Ov007BgLayer *func_ov007_020c95fc(void *a, int b, int c) {
    Ov007ScreenBlock f;
    Ctx ctx;
    Ov007ScreenBlock *p;

    if (a == 0) {
        return func_ov007_020c0aa8(0, b, c, 0x20, 0x18);
    }
    func_ov007_020c9a2c(&ctx, a);
    p = (Ov007ScreenBlock *)ctx.blockData[0];
    f = *p;
    return func_ov007_020c0aa8(p + 1, b, c, (u16)f.width, (u16)f.height);
}
