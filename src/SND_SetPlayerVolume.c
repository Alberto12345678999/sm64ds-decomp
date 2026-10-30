#include "types.h"

/* NitroSDK SND_interface.c SND_SetPlayerVolume: write the player's extFader
 * (offset 0x6, 2 bytes) in pret's SND_seq_shared.h SNDPlayer layout. */
extern void SNDi_SetPlayerParam(s32 player, u32 offset, u32 data, s32 size);

void SND_SetPlayerVolume(s32 player, s32 volume) {
    SNDi_SetPlayerParam(player, 0x6, volume, 2);
}
