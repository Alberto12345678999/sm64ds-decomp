//cpp
#include "types.h"
#include "IRQ.h"
#include "nitro/card/card_common.h"

extern "C" {

extern char rom_stat; /* rom_stat */

void func_02059f58(int a);  /* MI_StopDma */
int CARDi_TryReadCardDma(char *p); /* CARDi_TryReadCardDma */
void CARD_WaitRomAsync(void);
void CARDi_ReadRomSyncCore(CARDiCommon *c);

/* NitroSDK CARDi_ReadRom (card_rom.c): wait out the request in flight and
 * claim the card, record the transfer, then read by DMA if that can start
 * now, else run the read task (on the card thread if asynchronous). */
void CARDi_ReadRom(u32 dma, u32 src, u32 dst, u32 len, u32 callback, u32 arg, int is_async) {
    struct CARDiCommon *const c = &cardi_common;
    char *const p = &rom_stat;

    {
        u32 mask = IRQ::Disable();
        while (c->flag & 4)
            OS_SleepThread(&c->busy_q);
        c->flag |= 4;
        IRQ::Restore(mask);
    }

    c->dma = dma;
    c->src = src;
    c->dst = dst;
    c->len = len;
    c->callback = callback;
    c->callback_arg = arg;

    if (dma <= 3)
        func_02059f58(dma);

    if (CARDi_TryReadCardDma(p)) {
        if (!is_async)
            CARD_WaitRomAsync();
    } else if (is_async) {
        CARDi_SetTask(CARDi_ReadRomSyncCore);
    } else {
        c->cur_th = data_020a6134.current;
        CARDi_ReadRomSyncCore(c);
    }
}
}
