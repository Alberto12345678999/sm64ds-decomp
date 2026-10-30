#include "nitro/card/card_common.h"

extern void func_02061138(void);
extern void CARDi_ReadCard(void);
extern CARDiCommon cardi_common; /* cardi_common */
extern void *rom_stat;

#define MI_DMA_NOT_USE ((u32)~0)

/* NitroSDK CARD_Init: once, mark the block initialized and clear the
 * request, set up the card thread and PXI callback (CARDi_InitCommon), then
 * install CARDi_ReadCard (the ROM read routine) in rom_stat and call
 * func_02061138. */
void func_02060890(void)
{
    CARDiCommon *g = &cardi_common;
    if (g->flag != 0)
        return;
    g->flag = 1;
    g->len = 0;
    g->dst = g->len;
    g->src = g->dst;
    g->dma = MI_DMA_NOT_USE;
    g->callback = 0;
    g->callback_arg = 0;
    CARDi_InitCommon();
    rom_stat = (void *)CARDi_ReadCard;
    func_02061138();
}
