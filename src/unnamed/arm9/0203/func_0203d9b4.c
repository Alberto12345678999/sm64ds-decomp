/* This console's player index on the link (see func_0203d974.c). */
extern unsigned char data_020a0f10;

/* Nonzero only on the host: not a download-play child (boot type 2 at
   0x27ffc40) and player 0. The inverse of func_0203d974. */
int func_0203d9b4(void) {
    int b = (int)(*(unsigned short *)0x27ffc40 == 2);
    if (b != 0) return 0;
    return data_020a0f10 == 0;
}
