#include "types.h"

/* NitroSDK SND_interface.c SND_StopSeq: push command 1, pret's
 * SND_CMD_STOP_SEQ. */
extern void Snd_SendCommand(int id, int par1, int par2, int par3, int par4);

void SND_StopSeq(s32 player) {
    Snd_SendCommand(1, player, 0, 0, 0);
}
