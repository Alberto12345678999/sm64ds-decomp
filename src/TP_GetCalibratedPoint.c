/* NitroSDK SPI_tp.c TP_GetCalibratedPoint(disp, raw): copy the sample
 * while uncalibrated (data_020a80cc + 0x30), else keep touch/validity and
 * scale x/y by the calibration at data_020a80e4 (+0x18), clamped to the
 * 256x192 screen. */
extern unsigned short data_020a80cc[];
extern int data_020a80e4[];

/* NitroSDK TPData: one touch-panel sample. */
struct TPData {
    unsigned short x, y, touch, validity;
};

void TP_GetCalibratedPoint(struct TPData *disp, struct TPData *raw) {
    int *p;
    int t;
    if (data_020a80cc[0x18] == 0) {
        *disp = *raw;
        return;
    }
    p = data_020a80e4;
    disp->touch = raw->touch;
    disp->validity = raw->validity;
    if (raw->touch == 0) {
        disp->x = 0;
        disp->y = 0;
        return;
    }
    disp->x = (int)(((long long)p[2] * ((long long)(raw->x << 2) - (long long)p[0])) >> 22);
    t = (short)disp->x;
    if (t < 0) {
        disp->x = 0;
    } else if (t > 0xff) {
        disp->x = 0xff;
    }
    disp->y = (int)(((long long)p[5] * ((long long)(raw->y << 2) - (long long)p[3])) >> 22);
    t = (short)disp->y;
    if (t < 0) {
        disp->y = 0;
        return;
    }
    if (t > 0xbf) {
        disp->y = 0xbf;
    }
}
