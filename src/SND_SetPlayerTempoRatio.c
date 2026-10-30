#include "types.h"

/* NitroSDK SND_interface.c SND_SetPlayerTempoRatio: write the player's
 * tempoRatio (offset 0x1a, 2 bytes) in pret's SND_seq_shared.h SNDPlayer
 * layout. */
extern void SNDi_SetPlayerParam(s32 player, u32 offset, u32 data, s32 size);

void SND_SetPlayerTempoRatio(s32 player, s32 ratio) {
    SNDi_SetPlayerParam(player, 0x1a, ratio, 2);
}
