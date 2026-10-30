#include "types.h"

/* NitroSDK SND_interface.c SND_StartSeq: push command 0, pret's
 * SND_CMD_START_SEQ, with the sequence data, the offset into it and the bank.
 */
extern void Snd_SendCommand(int id, int par1, int par2, int par3, int par4);

void SND_StartSeq(s32 player, int seqBase, int seqOffset, int bank) {
    Snd_SendCommand(0, player, seqBase, seqOffset, bank);
}
