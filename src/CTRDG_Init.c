/* CTRDG_Init (the Nitro SDK's ctrdg.c): the cartridge PXI channel. */
#include "nitro/ctrdg/ctrdg_common.h"

#define PXI_FIFO_TAG_CTRDG 13
#define PXI_PROC_ARM7 1

extern void PXI_Init(void);
/* func_0205ba3c PXI_IsCallbackReady, func_0205ba64 PXI_SetFifoRecvCallback
 * (src/engine/pxi/PXI_Fifo.cpp). */
extern int func_0205ba3c(int tag, int proc);
extern void func_0205ba64(int tag, void *callback);
extern void func_0206a6d0(void);
extern void func_0206a694(void);
extern void func_0206a634(void);

extern int data_020a9de8; /* the init flag */
extern int data_020a9dec;

void CTRDG_Init(void) {
    if (data_020a9de8)
        return;
    data_020a9de8 = 1;
    CTRDGi_InitCommon();
    PXI_Init();
    while (func_0205ba3c(PXI_FIFO_TAG_CTRDG, PXI_PROC_ARM7) == 0)
        ;
    func_0205ba64(PXI_FIFO_TAG_CTRDG, (void *)func_0206a694);
    func_0206a6d0();
    func_0205ba64(PXI_FIFO_TAG_CTRDG, 0);
    func_0205ba64(PXI_FIFO_TAG_CTRDG, (void *)func_0206a634);
    data_020a9dec = 0;
}
