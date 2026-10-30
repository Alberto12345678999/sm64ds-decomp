#include "types.h"

/* NitroSDK SND_interface.c SND_SetTrackPan: write extPan (offset 0x9, 1 byte)
 * of each track in trackBitMask, in pret's SND_seq_shared.h SNDTrack layout. */
extern void SNDi_SetTrackParam(s32 player, u32 trackBitMask, u32 offset, u32 data, s32 size);

void SND_SetTrackPan(s32 player, u32 trackBitMask, s32 pan) {
    SNDi_SetTrackParam(player, trackBitMask, 0x9, pan, 1);
}
