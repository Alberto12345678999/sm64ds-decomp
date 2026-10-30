#include "types.h"
#include "Ov007PaletteBuf.h"

extern int func_ov007_020c3df4(int a, void *b);
extern void func_ov007_020c940c(Ov007PaletteBuf *buf);

/* Allocates a palette buffer on `source` and loads it. */
Ov007PaletteBuf *func_ov007_020c946c(const void *source) {
    Ov007PaletteBuf *buf = (Ov007PaletteBuf *)func_ov007_020c3df4(0, (void *)0x44);
    buf->source = source;
    func_ov007_020c940c(buf);
    return buf;
}
