#include "types.h"

/* NitroSDK SND_interface.c SNDi_SetTrackParam: push the track-param command
 * with the size packed above the player number. Snd_SendCommand is pret's
 * static PushCommand_impl; this SDK numbers the command 4 where pret's has 7.
 */
extern void Snd_SendCommand(int id, int par1, int par2, int par3, int par4);

void SNDi_SetTrackParam(s32 player, u32 trackBitMask, u32 offset, u32 data, s32 size) {
    Snd_SendCommand(4, player | (size << 24), trackBitMask, offset, data);
}
