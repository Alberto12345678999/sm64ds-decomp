/* PXI_Init (the Nitro SDK's pxi_init.c): a tail call to PXI_InitFifo
 * (src/engine/pxi/PXI_Fifo.cpp). */
extern void PXI_InitFifo(void);

void PXI_Init(void) {
    PXI_InitFifo();
}
