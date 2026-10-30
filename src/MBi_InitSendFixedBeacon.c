extern unsigned char data_020a9d2c;

#define G ((unsigned char *)&data_020a9d2c)

/* NitroSDK MBi_InitSendFixedBeacon (mb_gameinfo.c), beacon send state 2:
   set up the fixed part of the current game record.
   With its dataAttr byte (+0x4aa) zero the send starts at the record's first
   byte and takes 9 beacons; otherwise it starts past the 0x220-byte icon
   (palette, then character data, as MBi_MakeGameInfo lays them out) and takes
   4. Each beacon carries 0x62 bytes (MBi_SendFixedBeacon). Then go to state 3,
   MBi_SendFixedBeacon's fixed send. Only the state loop MB_SendGameInfoBeacon calls it. */
void MBi_InitSendFixedBeacon(void) {
    unsigned char *p;
    if (G[0xc] != 2)
        return;
    p = *(unsigned char **)(G + 4);
    if (p[0x4aa] == 0) {
        G[0x10] = 9;
        *(unsigned char **)(G + 8) = p;
    } else {
        G[0x10] = 4;
        *(unsigned char **)(G + 8) = p + 0x220;
    }
    G[0xc] = 3;
}
