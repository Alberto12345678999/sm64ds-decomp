/* NitroSDK SPI_tp.c TP_WaitBusy: spin while any command bit of mask is
 * still set in the TP state's command flags. */
#include "nitro/spi/tp.h"

void TP_WaitBusy(int mask) {
    while (data_020a80cc.mCommandFlags & mask)
        ;
}
