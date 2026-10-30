//cpp
/* NitroSDK CARDi_OnReadCard (card_rom.c): the card-data IRQ handler for a
 * DMA read. Advance a page; at the end stop the DMA (MI_StopDma), take the
 * card IRQ (IE bit 19) off and end the read, else start the next page. */
#include "IRQ.h"
#include "nitro/card/card_rom.h"

extern "C" {

extern void func_02059f58(int a); /* MI_StopDma */
extern void CARDi_ReadEnd(void);
extern void CARDi_SetCardDma(void);

void CARDi_OnReadCard(void) {
    cardi_common.src += CARD_ROM_PAGE_SIZE;
    cardi_common.dst += CARD_ROM_PAGE_SIZE;
    cardi_common.len -= CARD_ROM_PAGE_SIZE;
    if (cardi_common.len == 0) {
        func_02059f58(cardi_common.dma);
        IRQ::DisableIRQs(0x80000);
        IRQ::ClearInterrupts(0x80000);
        CARDi_ReadEnd();
    } else {
        CARDi_SetCardDma();
    }
}
}
