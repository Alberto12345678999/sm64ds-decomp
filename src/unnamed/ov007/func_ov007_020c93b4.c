#include "Ov007PaletteBuf.h"

extern void func_020555a4(void *dst);

/* Hands the buffer's colours to func_020555a4 as the toon table. */
void func_ov007_020c93b4(Ov007PaletteBuf *buf) {
    func_020555a4(buf->colors);
}
