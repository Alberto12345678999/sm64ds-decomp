#include "types.h"

/* NitroSDK SND_interface.c SND_SetTrackVolume: write extFader (offset 0xa, 2
 * bytes) of each track in trackBitMask, in pret's SND_seq_shared.h SNDTrack
 * layout. */
extern void SNDi_SetTrackParam(s32 player, u32 trackBitMask, u32 offset, u32 data, s32 size);

void SND_SetTrackVolume(s32 player, u32 trackBitMask, s32 volume) {
    SNDi_SetTrackParam(player, trackBitMask, 0xa, volume, 2);
}
