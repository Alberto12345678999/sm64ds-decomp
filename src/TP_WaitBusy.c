/* NitroSDK SPI_tp.c TP_WaitBusy: spin while any command bit of mask is
 * still set in the TP state's command flags. */
#include "nitro/spi/tp.h"
extern TPWork data_020a80cc;

void TP_WaitBusy(int mask) {
    while (data_020a80cc.mCommandFlags & mask)
        ;
}
