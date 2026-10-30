#include "types.h"

/* NitroSDK SND_interface.c SND_SetPlayerChannelPriority: write the player's
 * prio (offset 0x4, 1 byte) in pret's SND_seq_shared.h SNDPlayer layout. */
extern void SNDi_SetPlayerParam(s32 player, u32 offset, u32 data, s32 size);

void SND_SetPlayerChannelPriority(s32 player, s32 prio) {
    SNDi_SetPlayerParam(player, 0x4, prio, 1);
}
