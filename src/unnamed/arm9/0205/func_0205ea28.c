/* Transform a raw sample into screen coordinates: per axis,
   (coeff * ((raw << 2) - origin)) >> 22, clamped to 0xff and 0xbf, copying the
   touch and validity words through unchanged. Uncalibrated, the sample passes
   through as-is. The calibration words at +0x18 used to carry their own symbol
   row, data_020a80e4, although they are a member of the block this function
   also reads mCalibrated out of; see include/nitro/spi/tp.h. */
#include "nitro/spi/tp.h"
extern TPWork data_020a80cc;

void func_0205ea28(TPData *r0, TPData *r1) {
    int *p;
    int t;
    if (data_020a80cc.mCalibrated == 0) {
        *r0 = *r1;
        return;
    }
    p = data_020a80cc.mCalibration;
    r0->touch = r1->touch;
    r0->validity = r1->validity;
    if (r1->touch == 0) {
        r0->x = 0;
        r0->y = 0;
        return;
    }
    r0->x = (int)(((long long)p[2] * ((long long)(r1->x << 2) - (long long)p[0])) >> 22);
    t = (short)r0->x;
    if (t < 0) {
        r0->x = 0;
    } else if (t > 0xff) {
        r0->x = 0xff;
    }
    r0->y = (int)(((long long)p[5] * ((long long)(r1->y << 2) - (long long)p[3])) >> 22);
    t = (short)r0->y;
    if (t < 0) {
        r0->y = 0;
        return;
    }
    if (t > 0xbf) {
        r0->y = 0xbf;
    }
}
