#include "types.h"
extern char cardi_common[];
extern char rom_stat[];
extern void CARDi_SetRomOp(u32 a, u32 b);

/* One DMA channel's registers at 0x040000b0 + n * 0xc: source, destination,
 * control. */
typedef struct {
    u32 src;
    u32 dst;
    u32 ctrl;
} DmaCh;

/* The card access state block cardi_common (NitroSDK CARDiCommon), the
 * fields read here; names as func_02060890.c spells them. */
typedef struct CardCommon {
    unsigned char pad_00[0x18];
    int mSrc; /* 0x18 */
    int mDst; /* 0x1c */
    unsigned char pad_20[4];
    int mDma; /* 0x24 */
} CardCommon;

/* rom_stat: the ROM read routine func_02060890 installs (CARDi_ReadRomSyncCore
 * calls it with the block), then the ROMCTRL value written to 0x040001a4. */
typedef struct CardRomStat {
    void *read_func; /* 0x00 */
    u32 ctrl;        /* 0x04 */
} CardRomStat;

/* Start a card ROM read by DMA: point channel mDma at the card data port
 * (0x04100010) with mDst as the destination, send the read command for ROM
 * address mSrc (CARDi_SetRomOp), then start the card with ctrl. */
void CARDi_SetCardDma(void) {
    CardCommon *g = (CardCommon *)cardi_common;
    DmaCh *ch = (DmaCh *)(0x40000b0 + (g->mDma * 0xc));
    u32 v;
    ch->src = 0x4100010;
    ch->dst = g->mDst;
    ch->ctrl = 0xaf000001;
    v = g->mSrc;
    CARDi_SetRomOp((v >> 8) | 0xb7000000, v << 0x18);
    *((u32 *)0x40001a4) = ((CardRomStat *)rom_stat)->ctrl;
}
