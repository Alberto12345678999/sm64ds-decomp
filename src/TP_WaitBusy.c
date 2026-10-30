/* NitroSDK SPI_tp.c TP_WaitBusy: spin while any command bit of mask is
 * still set in the TP state's command flags. */
/* The TP state at data_020a80cc, as far as this function reads it. */
struct TPState {
    char pad[0x36];
    volatile unsigned short commandFlags; /* 0x36 */
};
extern struct TPState data_020a80cc;

void TP_WaitBusy(int mask) {
    while (data_020a80cc.commandFlags & mask)
        ;
}
