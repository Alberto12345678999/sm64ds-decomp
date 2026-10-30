extern int func_0203da3c(void);
extern void func_02060890(void);
extern void func_020603c8(int x);
extern void func_0205a588(void *p, int v, int n);
/* the 8-byte magic SaveData::SaveDataToCart writes with each block and
   ReadDataFromCart checks */
extern unsigned char data_020a4b40[];

/* Set up the save backup (func_0201a054 passes 0xd01 and "ds mario"):
   unless the link mode (func_0203da3c) is 2, which func_0203db64 sets on a
   download-play child, NitroSDK CARD_Init (func_02060890), then
   func_020603c8 with backup type a0, and keep src up to its NUL or 8
   bytes, zero-padded, as the save magic. 0xd01 reads as CARD_BACKUP_TYPE_EEPROM_64KBITS (device 1, size 2^13
   bytes), and func_020603c8 looks a table entry up by it
   (func_02060364), so it is likely CARD_IdentifyBackup. */
void func_02042f68(int a0, unsigned char *src) {
    int i;
    unsigned char *d;
    if (func_0203da3c() == 2)
        return;
    func_02060890();
    func_020603c8(a0);
    func_0205a588(data_020a4b40, 0, 8);
    d = data_020a4b40;
    for (i = 0; i < 8; i++) {
        unsigned char c = src[i];
        if (c == 0)
            return;
        *d++ = c;
    }
}
