#include "nitro/spi/tp.h"
extern TPWork data_020a80cc;
void func_0205ea10(int mask) {
    while (data_020a80cc.mCommandFlags & mask)
        ;
}
