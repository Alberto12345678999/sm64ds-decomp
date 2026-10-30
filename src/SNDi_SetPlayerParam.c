#include "types.h"

/* NitroSDK SND_interface.c SNDi_SetPlayerParam: push the player-param command.
 * Snd_SendCommand is pret's static PushCommand_impl; this SDK numbers the
 * command 3 where pret's has 6. */
extern void Snd_SendCommand(int id, int par1, int par2, int par3, int par4);

void SNDi_SetPlayerParam(s32 player, u32 offset, u32 data, s32 size) {
    Snd_SendCommand(3, player, offset, data, size);
}
