#include "types.h"

/* func_ov007_020c946c's 0x44-byte palette buffer. */
typedef struct Ov007PaletteBuf {
    const void *source; /* 0x00 */
    u16 colors[0x20];   /* 0x04 */
} Ov007PaletteBuf;

extern unsigned short func_ov007_020c3be0(int t, int a, int b);

/* Blends all 32 colours: out = from at t = 0, to at t = 0x1000 (Q12). */
void func_ov007_020c93c4(int t, Ov007PaletteBuf *from, Ov007PaletteBuf *to, Ov007PaletteBuf *out) {
    int i = 0;
    u16 *fromColors = from->colors;
    u16 *toColors = to->colors;
    do {
        out->colors[i] = func_ov007_020c3be0(t, fromColors[i], toColors[i]);
        i++;
    } while (i < 0x20);
}
