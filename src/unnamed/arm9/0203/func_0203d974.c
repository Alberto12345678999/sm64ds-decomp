/* data_020a0f10 is this console's player index on the link: the AID that
   func_0203ea5c takes from func_02040704, 0 for the parent. */
extern unsigned char data_020a0f10;

/* Nonzero unless this console is the host: a download-play child (boot type
   2 at 0x27ffc40, NitroSDK's MB_IsMultiBootChild) or any player but 0.
   func_0203d9b4 is the same test the other way round. */
int func_0203d974(void) {
    int b = (int)(*(unsigned short *)0x27ffc40 == 2);
    if (b != 0) return 1;
    return data_020a0f10 != 0;
}
