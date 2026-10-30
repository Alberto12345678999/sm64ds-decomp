extern int GetPlayerFlagByte(int a0, int a1);
/* Bit 3 of player a0's link settings byte 0: the ready bit
   func_02020334 sets. */
unsigned char func_02020364(int a0) {
    return GetPlayerFlagByte(a0, 0) & 8;
}
