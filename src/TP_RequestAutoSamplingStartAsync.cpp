//cpp
/* NitroSDK SPI_tp.c TP_RequestAutoSamplingStartAsync(vcount, frequency,
 * samplingBufs, bufSize): record the ring, clear each sample's touch, then
 * send the auto-sampling command 1 (flag 2) over PXI tag 6. */
#include "types.h"
#include "IRQ.h"
extern "C" {
int PXI_SendWordByFifo(unsigned int a, unsigned int c, unsigned int b);
}

struct S {
    void (*fn)(int, int, int);
    char pad4[0xc - 4];
    u16 fc;
    u16 fe;
    int f10;
    u16 f14;
    char pad16[0x34 - 0x16];
    volatile u16 f34;
    volatile u16 f36;
};
extern S data_020a80cc;

#pragma opt_strength_reduction off
extern "C" void TP_RequestAutoSamplingStartAsync(unsigned int vcount, unsigned int frequency,
                                                 int samplingBufs, unsigned int bufSize) {
    unsigned int i;
    unsigned int irq;
    int ok;

    data_020a80cc.f10 = samplingBufs;
    data_020a80cc.fc = 0;
    data_020a80cc.fe = (u16)frequency;
    data_020a80cc.f14 = (u16)bufSize;
    for (i = 0; i < bufSize; i++) {
        *(u16 *)(data_020a80cc.f10 + (i << 3) + 4) = 0;
    }
    irq = IRQ::Disable();
    if (PXI_SendWordByFifo(6, (frequency & 0xff) | 0x2000100, 0) < 0)
        ok = 0;
    else if (PXI_SendWordByFifo(6, vcount | 0x1010000, 0) < 0)
        ok = 0;
    else
        ok = 1;
    if ((ok & 0xff) == 0) {
        IRQ::Restore(irq);
        data_020a80cc.f34 |= 2;
        if (data_020a80cc.fn != 0)
            data_020a80cc.fn(1, 4, 0);
        return;
    }
    data_020a80cc.f36 |= 2;
    data_020a80cc.f34 &= ~2;
    IRQ::Restore(irq);
}
