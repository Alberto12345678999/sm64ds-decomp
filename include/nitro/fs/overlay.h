#ifndef NITRO_FS_OVERLAY_H
#define NITRO_FS_OVERLAY_H

/*
 * NitroSDK FSOverlayInfo, the record FS_LoadOverlayInfo (and the game's
 * copy of it, func_02018c00) fills: overlay `id`'s 0x20-byte entry from the overlay table, then the
 * target processor at +0x20. The names are the SDK's, as pret's pokediamond
 * FS_overlay.h spells them. That later SDK appends a CARDRomRegion
 * file_pos after target (0x2c bytes); this one stops at 0x24, the size
 * the byte-matched stack frames of LoadOverlay, UnloadOverlay and
 * FS_LoadOverlay reserve.
 */

#include "types.h"

typedef void (*FSOverlayInitFunc)(void);

typedef struct FSOverlayInfoHeader {
    u32 id;                            /* 0x00 */
    u8 *ram_address;                   /* 0x04 */
    u32 ram_size;                      /* 0x08 */
    u32 bss_size;                      /* 0x0c */
    FSOverlayInitFunc *sinit_init;     /* 0x10 */
    FSOverlayInitFunc *sinit_init_end; /* 0x14 */
    u32 file_id;                       /* 0x18 */
    u32 compressed : 24;               /* 0x1c */
    u32 flag : 8;
} FSOverlayInfoHeader;

typedef struct FSOverlayInfo {
    FSOverlayInfoHeader header; /* 0x00 */
    int target;                 /* 0x20 -- MIProcessor: 0 ARM9, 1 ARM7 */
} FSOverlayInfo;

typedef char FSOverlayInfo_size_must_be_0x24[sizeof(FSOverlayInfo) == 0x24 ? 1 : -1];

#endif
