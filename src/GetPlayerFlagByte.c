extern unsigned char data_020a1166[];
/* Byte p of player i's link settings: bytes 0x12.. of the players' 0x24-byte
   input records (data_020a1154, so data_020a1166 is the first one's 0x12).
   func_0203db3c writes the same bytes in this console's own record,
   data_020a1040. The accessors func_02020028..func_02020388 give the bits
   their roles (ready, go, course, slot mask, controller mode). */
unsigned char GetPlayerFlagByte(int i, int p) {
    return *(unsigned char *)((char *)data_020a1166 + i * 0x24 + p);
}
