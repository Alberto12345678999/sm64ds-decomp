#include "types.h"

/* NitroSDK SND_interface.c SND_SetTrackPitch: write extPitch (offset 0xc, 2
 * bytes) of each track in trackBitMask, in pret's SND_seq_shared.h SNDTrack
 * layout. */
extern void SNDi_SetTrackParam(s32 player, u32 trackBitMask, u32 offset, u32 data, s32 size);

void SND_SetTrackPitch(s32 player, u32 trackBitMask, s32 pitch) {
    SNDi_SetTrackParam(player, trackBitMask, 0xc, pitch, 2);
}
