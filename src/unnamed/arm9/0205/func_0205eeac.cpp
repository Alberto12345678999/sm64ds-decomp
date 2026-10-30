//cpp
#include "types.h"
#include "nitro/spi/tp.h"
extern "C" {
int IPCSend(unsigned int a, unsigned int c, unsigned int b);
}
namespace IRQ { unsigned int Disable(); void Restore(unsigned int); }

/* C linkage: data_020a80cc is a ROM data symbol named by its exact final name,
   so a C++ translation unit must not mangle it. mwccarm leaves a data extern
   unmangled either way, but the PC port links this file with MSVC, which does
   not -- that is the failure #4493 hit on the split IRQ files. */
extern "C" TPWork data_020a80cc;

#pragma opt_strength_reduction off
extern "C" void func_0205eeac(unsigned int a, unsigned int b, int x, unsigned int count)
{
    unsigned int i;
    unsigned int irq;
    int ok;

    data_020a80cc.mSamplingBufs = (TPData *)x;
    data_020a80cc.mIndex = 0;
    data_020a80cc.mFrequency = (u16)b;
    data_020a80cc.mBufSize = (u16)count;
    for (i = 0; i < count; i++) {
        data_020a80cc.mSamplingBufs[i].touch = 0;
    }
    irq = IRQ::Disable();
    if (IPCSend(6, (b & 0xff) | 0x2000100, 0) < 0)
        ok = 0;
    else if (IPCSend(6, a | 0x1010000, 0) < 0)
        ok = 0;
    else
        ok = 1;
    if ((ok & 0xff) == 0) {
        IRQ::Restore(irq);
        data_020a80cc.mErrFlags |= 2;
        if (data_020a80cc.mCallback != 0)
            data_020a80cc.mCallback(1, 4, 0);
        return;
    }
    data_020a80cc.mCommandFlags |= 2;
    data_020a80cc.mErrFlags &= ~2;
    IRQ::Restore(irq);
}
