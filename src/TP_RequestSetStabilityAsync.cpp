//cpp
/* NitroSDK SPI_tp.c TP_RequestSetStabilityAsync(retry, range): send
 * the set-stability command (3) to the ARM7 over PXI tag 6 and mark its
 * command bit (8); on a send failure set its error bit and report
 * (3, 4, 0) to the user callback. */
#include "types.h"
#include "IRQ.h"
#include "nitro/spi/tp.h"
extern "C" {
int PXI_SendWordByFifo(int a, int b, int c);
}
/* C linkage: data_020a80cc is a ROM data symbol named by its exact final name,
   so a C++ translation unit must not mangle it. mwccarm leaves a data extern
   unmangled either way, but the PC port links this file with MSVC, which does
   not -- that is the failure #4493 hit on the split IRQ files. */
extern "C" TPWork data_020a80cc;
extern "C" void TP_RequestSetStabilityAsync(int a, int b) {
    unsigned int irq = IRQ::Disable();
    int ok;
    if (PXI_SendWordByFifo(6, a | 0x2000300, 0) < 0)
        ok = 0;
    else if (PXI_SendWordByFifo(6, b | 0x1010000, 0) < 0)
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
