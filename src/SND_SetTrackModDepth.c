#include "types.h"

/* NitroSDK SND_interface.c SND_SetTrackModDepth: write mod.depth (offset 0x1a,
 * 1 byte) of each track in trackBitMask, in pret's SND_seq_shared.h SNDTrack
 * layout. */
extern void SNDi_SetTrackParam(s32 player, u32 trackBitMask, u32 offset, u32 data, s32 size);

void SND_SetTrackModDepth(s32 player, u32 trackBitMask, s32 depth) {
    SNDi_SetTrackParam(player, trackBitMask, 0x1a, depth, 1);
}
