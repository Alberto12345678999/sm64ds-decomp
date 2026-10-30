/* NitroSDK CARD_WaitRomAsync (card_rom.c): wait for the card request in
 * flight. CARDi_ReadRom calls it after starting a synchronous DMA read.
 */
#include "nitro/card/card_common.h"

void CARD_WaitRomAsync(void) {
    CARDi_WaitAsync();
}
