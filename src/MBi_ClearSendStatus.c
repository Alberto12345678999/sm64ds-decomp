extern unsigned char data_020a9d2c[];
/* NitroSDK MBi_ClearSendStatus (mb_gameinfo.c): clear the per-record send
   counters of the beacon send status
   data_020a9d2c: bytes 0xd..0x11, i.e. the latched seqNoVolat (0xe), the
   fixed-beacon index and count (0xf, 0x10) and beaconNo (0x11). Called when
   func_02068398 picks the next record and from MB_InitSendGameInfoStatus. */
void MBi_ClearSendStatus(void) {
    data_020a9d2c[0xd] = 0;
    data_020a9d2c[0xe] = 0;
    data_020a9d2c[0xf] = 0;
    data_020a9d2c[0x10] = 0;
    data_020a9d2c[0x11] = 0;
}
