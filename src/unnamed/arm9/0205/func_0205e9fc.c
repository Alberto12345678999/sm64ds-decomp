#include "nitro/spi/tp.h"
extern TPWork data_020a80cc;
int func_0205e9fc(int mask) {
    return data_020a80cc.mErrFlags & mask;
}
