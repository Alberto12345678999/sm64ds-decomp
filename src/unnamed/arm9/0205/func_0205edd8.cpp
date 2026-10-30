//cpp
#include "types.h"
#include "nitro/spi/tp.h"
extern "C" {
int IPCSend(int a, int b, int c);
}
namespace IRQ { unsigned int Disable(); void Restore(unsigned int); }
/* C linkage: data_020a80cc is a ROM data symbol named by its exact final name,
   so a C++ translation unit must not mangle it. mwccarm leaves a data extern
   unmangled either way, but the PC port links this file with MSVC, which does
   not -- that is the failure #4493 hit on the split IRQ files. */
extern "C" TPWork data_020a80cc;
extern "C" void func_0205edd8(int a, int b)
{
    unsigned int irq = IRQ::Disable();
    int ok;
    if (IPCSend(6, a | 0x2000300, 0) < 0)
        ok = 0;
    else if (IPCSend(6, b | 0x1010000, 0) < 0)
        ok = 0;
    else
        ok = 1;
    if (ok == 0) {
        IRQ::Restore(irq);
        data_020a80cc.mErrFlags |= 8;
        if (data_020a80cc.mCallback != 0)
            data_020a80cc.mCallback(3, 4, 0);
        return;
    }
    data_020a80cc.mCommandFlags |= 8;
    data_020a80cc.mErrFlags &= ~8;
    IRQ::Restore(irq);
}
