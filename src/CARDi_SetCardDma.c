/* NitroSDK CARDi_SetCardDma (card_rom.c): start a card ROM read by DMA.
 * Point channel dma at the card data port with dst as the destination, send
 * the read command for ROM address src (CARDi_SetRomOp), then start the card
 * with rom_stat's ctrl. */
#include "nitro/card/card_rom.h"

#define REG_CARD_CNT (*(volatile u32 *)0x040001a4)

extern void CARDi_SetRomOp(u32 cmd1, u32 cmd2);

/* One DMA channel's registers at 0x040000b0 + n * 12: source, destination,
 * control. */
typedef struct {
    u32 src;
    u32 dst;
    u32 ctrl;
} DmaCh;

void CARDi_SetCardDma(void) {
    CARDiCommon *const c = &cardi_common;
    CARDRomStat *const p = &rom_stat;
    DmaCh *ch = (DmaCh *)(0x040000b0 + c->dma * 12);
    ch->src = 0x04100010;
    ch->dst = c->dst;
    ch->ctrl = 0xaf000001;
    CARDi_SetRomOp((c->src >> 8) | 0xb7000000, c->src << 24);
    REG_CARD_CNT = p->ctrl;
}
