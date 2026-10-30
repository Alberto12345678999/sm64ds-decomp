//cpp
#include "CP15.h"
#include "IRQ.h"
#include "nitro/ctrdg/ctrdg_common.h"

extern "C" {

extern void DMASyncHalfTransfer(unsigned int channel, void *src, void *dst, unsigned int numHalfs);
extern void MultiCopy_Int(int *dst, int *src, int len);
extern void WaitByLoop(int n);

extern int data_020a9de4;
extern CTRDGWork data_020a9de0; /* CTRDGi_Work */
/* data_020a9e00 is a 0xc0-byte copy of the CTRDGHeader at 0x08000000; the
 * DMA below fills its last 0x40 bytes (+0x80) from the cartridge, and the
 * BIOS logo goes into nintendoLogo (data_020a9e04). */
extern int data_020a9e00;
extern int data_020a9e04;

#define CTRDG_MODULE_INFO ((volatile CTRDGModuleInfo *)0x27ffc30)
#define CTRDG_HEADER (*(CTRDGHeader *)&data_020a9e00)

#pragma opt_strength_reduction off

void func_0206a6d0(void)
{
    int sp[4];
    unsigned int irq;
    int flag;
    u16 save208;
    int i;
    u32 data;

    if (data_020a9de4 != 0)
        return;
    data_020a9de4 = 1;
    if ((*(volatile u16 *)0x4000300 & 1) == 0)
        return;
    irq = IRQ::SetIRQs(0x40000);
    save208 = *(volatile u16 *)0x4000208;
    *(volatile u16 *)0x4000208 = 1;
    CTRDGi_LockByProcessor(data_020a9de0.lockID, sp);
    flag = ((int)*(volatile u16 *)0x4000204 & 0x8000) >> 15;
    CTRDGi_ChangeLatestAccessCycle(sp + 2);
    *(volatile u16 *)0x4000204 &= ~0x8000;
    DMASyncHalfTransfer(0, (void *)0x8000080, (void *)((char *)&CTRDG_HEADER + 0x80), 0x40);
    *(volatile u16 *)0x4000204 = (*(volatile u16 *)0x4000204 & ~0x8000) | (flag << 15);
    CTRDGi_RestoreAccessCycle(sp + 2);
    CTRDGi_UnlockByProcessor(data_020a9de0.lockID, sp);
    CTRDG_MODULE_INFO->moduleID = CTRDG_HEADER.moduleID;
    for (i = 0; i < 3; i++)
        /* Indexed off a typed pointer, not `*(volatile u8 *)(0x27ffc32 + i)`. Under
           2004/b56 the integer form parks the whole address in the literal pool and
           stores through a register offset, while the ROM builds 0x27ff000 from two
           immediates and puts 0xc32 in the store's 12-bit displacement -- one more
           instruction and one FEWER literal. That single pool entry shifts every
           pc-relative load in the function by 4, which is the whole 52-word diff. */
        CTRDG_MODULE_INFO->exLsiID[i] = CTRDG_HEADER.exLsiID[i];
    {
        /* Through a local: writing these two through CTRDG_MODULE_INFO as
           well moves the bytes. */
        volatile CTRDGModuleInfo *info = CTRDG_MODULE_INFO;
        info->makerCode = CTRDG_HEADER.makerCode;
        info->gameCode = CTRDG_HEADER.gameCode;
    }
    MultiCopy_Int((int *)0xffff0020, &data_020a9e04, 0x9c);
    CP15::FlushAndInvalidateDataCache();
    data = (((unsigned int)&data_020a9e00 + 0xfe000000) >> 5) << 6 | 1;
    CTRDGi_SendtoPxi(data);
    if (data_020a9de0.subpState != 1) {
        do {
            WaitByLoop(1);
        } while (data_020a9de0.subpState != 1);
    }
    (void)*(volatile u16 *)0x4000208;
    *(volatile u16 *)0x4000208 = save208;
    IRQ::SetIRQs(irq);
}
}
