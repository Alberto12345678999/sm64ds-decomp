#include "types.h"

/* NitroSDK SND_interface.c SND_SetTrackModSpeed: write mod.speed (offset 0x19,
 * 1 byte) of each track in trackBitMask, in pret's SND_seq_shared.h SNDTrack
 * layout. */
extern void SNDi_SetTrackParam(s32 player, u32 trackBitMask, u32 offset, u32 data, s32 size);

void SND_SetTrackModSpeed(s32 player, u32 trackBitMask, s32 speed) {
    SNDi_SetTrackParam(player, trackBitMask, 0x19, speed, 1);
}
