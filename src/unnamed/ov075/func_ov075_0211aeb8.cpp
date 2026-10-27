//cpp
#include "nitro/fx/fx.h"
#include "cstd.h"

extern "C" {

short func_ov075_0211aeb8(char *c, int x) {
    int t = cstd::fdiv(0xffff, 0x16c000);
    int v = FX_MUL(x, t);
    return (short)(v - *(short *)(c + 0xa0));
}
}
