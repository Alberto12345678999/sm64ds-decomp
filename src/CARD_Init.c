/* NitroSDK CARD_Init (card_rom.c): once, mark the block initialized and
 * clear the request, set up the card thread and PXI callback
 * (CARDi_InitCommon), install CARDi_ReadCard as rom_stat's read routine, then
 * call func_02061138 (where pret calls CARD_InitPulledOutCallback). This SDK
 * has no cardi_rom_base and no CARDi_GetRomAccessor. */
#include "nitro/card/card_rom.h"

extern void func_02061138(void);

void CARD_Init(void) {
    CARDiCommon *const p = &cardi_common;

    if (!p->flag) {
        p->flag = CARD_STAT_INIT;
        p->src = p->dst = p->len = 0;
        p->dma = (u32)~0;
        p->callback = 0;
        p->callback_arg = 0;

        CARDi_InitCommon();

        rom_stat.read_func = CARDi_ReadCard;

        func_02061138();
    }
}
