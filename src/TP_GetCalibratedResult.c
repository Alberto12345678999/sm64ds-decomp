/* NitroSDK SPI_tp.c TP_GetCalibratedResult: 1 on a sampling error,
 * else the last sample (data_020a80cc + 0x4) calibrated in place and 0. */
/* NitroSDK TPData: one touch-panel sample. */
struct TPData {
    unsigned short x, y, touch, validity;
};
struct G {
    unsigned short pad0[2];
    struct TPData buf;
    unsigned char pad1[0x34 - 0xc];
    unsigned short errFlags;
};

extern struct G data_020a80cc;
extern void TP_GetCalibratedPoint(struct TPData *disp, struct TPData *raw);

int TP_GetCalibratedResult(struct TPData *result) {
    if (data_020a80cc.errFlags & 1)
        return 1;
    *result = data_020a80cc.buf;
    TP_GetCalibratedPoint(result, result);
    return 0;
}
