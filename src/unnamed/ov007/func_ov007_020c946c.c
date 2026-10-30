#include "types.h"

/* The 0x44-byte palette buffer: func_ov007_020c940c copies 0x40 bytes of
 * colours from source into colors, or clears them when source is 0. */
typedef struct Ov007PaletteBuf {
    const void *source; /* 0x00 */
    u16 colors[0x20];   /* 0x04 */
} Ov007PaletteBuf;

extern int func_ov007_020c3df4(int a, void *b);
extern void func_ov007_020c940c(void *buf);

/* Allocates a palette buffer on `source` and loads it. */
void *func_ov007_020c946c(void *source) {
    Ov007PaletteBuf *buf = (Ov007PaletteBuf *)func_ov007_020c3df4(0, (void *)0x44);
    buf->source = source;
    func_ov007_020c940c(buf);
    return buf;
}
