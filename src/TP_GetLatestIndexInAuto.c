/* NitroSDK SPI_tp.c TP_GetLatestIndexInAuto: the auto-sampling ring
 * index. */
/* The TP state at data_020a80cc, as far as this function reads it. */
struct TPState {
    char pad[0xc];
    unsigned short index; /* 0x0c */
};
extern struct TPState data_020a80cc;

int TP_GetLatestIndexInAuto(void) {
    return data_020a80cc.index;
}
