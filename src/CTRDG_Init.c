/* CTRDG_Init (the Nitro SDK's ctrdg.c): the cartridge PXI channel. */
#include "nitro/ctrdg/ctrdg_common.h"

#define PXI_FIFO_TAG_CTRDG 13
#define PXI_PROC_ARM7 1

extern void PXI_Init(void);
/* PXI_IsCallbackReady and PXI_SetFifoRecvCallback (src/engine/pxi/PXI_Fifo.cpp). */
extern int PXI_IsCallbackReady(int tag, int proc);
extern void PXI_SetFifoRecvCallback(int tag, void *callback);
extern void func_0206a6d0(void);
extern void func_0206a694(int tag, int data);
extern void func_0206a634(int tag, int data);

extern int data_020a9de8;         /* the init flag */
extern int (*data_020a9dec)(int); /* the hook func_0206a634 (func_0206a600.c) calls */

void CTRDG_Init(void) {
    if (data_020a9de8)
        return;
    data_020a9de8 = 1;
    CTRDGi_InitCommon();
    PXI_Init();
    while (PXI_IsCallbackReady(PXI_FIFO_TAG_CTRDG, PXI_PROC_ARM7) == 0)
        ;
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_CTRDG, (void *)func_0206a694);
    func_0206a6d0();
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_CTRDG, 0);
    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_CTRDG, (void *)func_0206a634);
    data_020a9dec = 0;
}
