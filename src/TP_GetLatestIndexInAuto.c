/* NitroSDK SPI_tp.c TP_GetLatestIndexInAuto: the auto-sampling ring
 * index. */
#include "nitro/spi/tp.h"
extern TPWork data_020a80cc;

int TP_GetLatestIndexInAuto(void) {
    return data_020a80cc.mIndex;
}
