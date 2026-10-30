extern int GetPlayerFlagByte(int a0, int a1);
/* Bit 4 of player a0's link settings byte 2: the rematch ready bit
   func_020201c0 sets. */
unsigned char func_020201f0(int a0) {
    return GetPlayerFlagByte(a0, 2) & 0x10;
}
