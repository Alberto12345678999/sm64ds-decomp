//cpp
#include "IRQ.h"
#include "nitro/spi/tp.h"

extern "C" {

int IPCSend(int cmd, int a, int b);

extern TPWork data_020a80cc;

void func_0205f040(void)
{
    unsigned int saved = IRQ::Disable();
    int ok = (IPCSend(6, 0x3000000, 0) >= 0);
    if (!ok) {
        void (*fp)(int,int,int);
        IRQ::Restore(saved);
        fp = data_020a80cc.mCallback;
        data_020a80cc.mErrFlags |= 1;
        if (fp == 0) return;
        fp(0, 4, 0);
        return;
    }
    data_020a80cc.mCommandFlags |= 1;
    data_020a80cc.mErrFlags &= ~1;
    IRQ::Restore(saved);
}
}
