struct G9d2c {
    char pad0[4];
    unsigned char *p;
    char pad8[4];
    unsigned char c;
    unsigned char pad_d;
    unsigned char e;
};
extern struct G9d2c data_020a9d2c;

/* Beacon send state 4: start the volatile part of the current game record
   (data_020a9d2c.p, MBGameInfo). Mark the parent's bit (1) in its
   broadcastedPlayerFlag (+0x4a8), latch its seqNoVolat (+0x4ac) into the send
   status (+0xe), and go to state 5, func_02067f68's volatile send. The
   state loop func_02068410 calls it, and func_02067f68 calls it again when
   that latched copy goes stale. */
void func_02068188(void) {
    *(short *)(data_020a9d2c.p + 0x4a8) = 1;
    data_020a9d2c.e = data_020a9d2c.p[0x4ac];
    data_020a9d2c.c = 5;
}
