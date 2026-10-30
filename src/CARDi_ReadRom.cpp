//cpp
#include "types.h"
#include "IRQ.h"
#include "nitro/card/card_common.h"

extern "C" {

/* NitroSDK CARDiCommon (cardi_common), the fields this function touches. */
struct CARDiCommon {
    char pad0[0x18];
    u32 src;          /* 0x18 */
    u32 dst;          /* 0x1c */
    u32 len;          /* 0x20 */
    u32 dma;          /* 0x24 */
    u32 callback;     /* 0x28 */
    u32 callback_arg; /* 0x2c */
    char pad30[4];
    volatile u32 flag; /* 0x34 -- CARD_STAT_*: 4 busy */
    char pad38[0xd0 - 0x38];
    u32 cur_th;  /* 0xd0 */
    char busy_q; /* 0xd4 -- OSThreadQueue */
};

/* OSi_ThreadInfo; current is the running thread. */
struct OSThreadInfo {
    char pad[8];
    u32 current;
};

extern struct CARDiCommon data_020a8180; /* cardi_common */
extern char data_020a8780;               /* rom_stat */
extern struct OSThreadInfo data_020a6134;

void OS_SleepThread(void *p);
void func_02059f58(int a);  /* MI_StopDma */
int func_02060b64(char *p); /* CARDi_TryReadCardDma */
void CARD_WaitRomAsync(void);
void CARDi_ReadRomSyncCore(void *c);

/* NitroSDK CARDi_ReadRom (card_rom.c): wait out the request in flight and
 * claim the card, record the transfer, then read by DMA if that can start
 * now, else run the read task (on the card thread if asynchronous). */
void CARDi_ReadRom(u32 dma, u32 src, u32 dst, u32 len, u32 callback, u32 arg, int is_async) {
    struct CARDiCommon *const c = &data_020a8180;
    char *const p = &data_020a8780;

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

    if (func_02060b64(p)) {
        if (!is_async)
            CARD_WaitRomAsync();
    } else if (is_async) {
        CARDi_SetTask((void *)CARDi_ReadRomSyncCore);
    } else {
        c->cur_th = data_020a6134.current;
        CARDi_ReadRomSyncCore(c);
    }
}
}
