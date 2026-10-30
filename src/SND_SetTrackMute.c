#include "types.h"

/* NitroSDK SND_interface.c SND_SetTrackMute: push the mute-track command, 5
 * here, the one after the track-param command as in pret's numbering. */
extern void Snd_SendCommand(int id, int par1, int par2, int par3, int par4);

void SND_SetTrackMute(s32 player, u32 trackBitMask, int flag) {
    Snd_SendCommand(5, player, trackBitMask, flag, 0);
}
