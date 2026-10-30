#include "nitro/spi/tp.h"

extern TPWork data_020a80cc;
extern void func_0205ea28(TPData *p, TPData *q);

int func_0205efe0(TPData *dest) {
    if (data_020a80cc.mErrFlags & 1)
        return 1;
    *dest = data_020a80cc.mBuf;
    func_0205ea28(dest, dest);
    return 0;
}
