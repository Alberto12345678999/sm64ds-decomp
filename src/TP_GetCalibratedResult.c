/* NitroSDK SPI_tp.c TP_GetCalibratedResult: 1 on a sampling error,
 * else the last sample (mBuf) calibrated in place and 0. */
#include "nitro/spi/tp.h"

extern TPWork data_020a80cc;
extern void TP_GetCalibratedPoint(TPData *disp, TPData *raw);

int TP_GetCalibratedResult(TPData *result) {
    if (data_020a80cc.mErrFlags & 1)
        return 1;
    *result = data_020a80cc.mBuf;
    TP_GetCalibratedPoint(result, result);
    return 0;
}
