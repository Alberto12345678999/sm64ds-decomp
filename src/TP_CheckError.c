/* NitroSDK SPI_tp.c TP_CheckError: the error bits of mask in the TP
 * state's error flags. */
/* The TP state at data_020a80cc, as far as this function reads it. */
struct TPState {
    char pad[0x34];
    unsigned short errFlags; /* 0x34 */
};
extern struct TPState data_020a80cc;

int TP_CheckError(int mask) {
    return data_020a80cc.errFlags & mask;
}
