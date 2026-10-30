/* MI_SendGXCommand at 0x01ffde98 (ITCM) -- NitroSDK. Synchronous 32-bit DMA of a
 * geometry command list into the command FIFO (REG_GXFIFO, 0x04000400), split into
 * transfers of at most 118 words (the SDK's MIi_GX_LENGTH_ONCE, 0x1d8 bytes). It waits
 * for the channel before the first transfer and again after the last.
 *
 * Identified by its body and placement: pret/pokediamond's MI_dma_gxcommand.c has the
 * same function, the same chunk size and the same two waits, inside
 * `#pragma section ITCM`. DMAStartTransfer is the SDK's MIi_DmaSetParams.
 */

#include "nitro/hw/registers.h"

#define DMA_CONTROL_DEST_FIXED (2u << 21)
#define GXFIFO_DMA_CONTROL (DMA_CONTROL_ENABLE | DMA_CONTROL_32_BIT | DMA_CONTROL_DEST_FIXED)

extern void DMAStartTransfer(u32 channel, void *src, void *dst, u32 cnt);

void MI_SendGXCommand(u32 dmaNo, void *src, u32 commandLength) {
    volatile u32 *dmaCtrl;
    void *fifo;
    u32 chunk;

    if (commandLength == 0)
        return;

    dmaCtrl = REG_DMA_CNT_PTR(dmaNo);

    while (*dmaCtrl & DMA_CONTROL_ENABLE)
        ;

    fifo = (void *)0x04000400;
    while (commandLength != 0) {
        chunk = commandLength > 0x1d8 ? 0x1d8 : commandLength;
        DMAStartTransfer(dmaNo, src, fifo, GXFIFO_DMA_CONTROL | (chunk >> 2));
        commandLength -= chunk;
        src = (u8 *)src + chunk;
    }

    while (*dmaCtrl & DMA_CONTROL_ENABLE)
        ;
}
