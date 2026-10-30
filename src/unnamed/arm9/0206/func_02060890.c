#include "nitro/card/card_common.h"

extern void func_02061138(void);
extern void func_02060a64(void);
extern CARDiCommon data_020a8180; /* cardi_common */
extern void *data_020a8780;

#define MI_DMA_NOT_USE ((u32)~0)

/* NitroSDK CARD_Init: once, mark the block initialized and clear the
 * request, set up the card thread and PXI callback (CARDi_InitCommon), then
 * install func_02060a64 (the ROM read routine) in data_020a8780 and call
 * func_02061138. */
void func_02060890(void)
{
    CARDiCommon *g = &data_020a8180;
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
    data_020a8780 = (void *)func_02060a64;
    func_02061138();
}
