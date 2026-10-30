/* OS_InitReset (the Nitro SDK's os_reset.c): listen for the ARM7's reset
 * command on the OS PXI channel. */
#include "types.h"

#define PXI_FIFO_TAG_OS 12
#define PXI_PROC_ARM7 1

extern void PXI_Init(void);
/* func_0205ba3c PXI_IsCallbackReady, func_0205ba64 PXI_SetFifoRecvCallback
 * (src/engine/pxi/PXI_Fifo.cpp); func_02059e04 OSi_CommonCallback. */
extern int func_0205ba3c(int tag, int proc);
extern void func_0205ba64(int tag, void *callback);
extern void func_02059e04(void);

extern u16 data_020a6458; /* OSi_IsInitReset */

void OS_InitReset(void) {
    if (data_020a6458 != 0)
        return;
    data_020a6458 = 1;
    PXI_Init();
    while (func_0205ba3c(PXI_FIFO_TAG_OS, PXI_PROC_ARM7) == 0)
        ;
    func_0205ba64(PXI_FIFO_TAG_OS, (void *)func_02059e04);
}
