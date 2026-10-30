extern char data_020a1052[];
/* Byte i of this console's link settings, at 0x12 of its own input record
   data_020a1040 (data_020a1052): the writer the 0202 accessors pair with
   GetPlayerFlagByte. */
void func_0203db3c(int i, int v) {
    data_020a1052[i] = v;
}
