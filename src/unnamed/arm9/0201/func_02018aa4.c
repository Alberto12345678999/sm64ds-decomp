extern int func_0205d89c(int);
extern int func_02017e60(void);

/* Bring up the file system at boot (func_0201a054): func_0205d89c is
   NitroSDK's FS_Init (once only, guarded by data_020a8058), here with DMA
   channel 2, then every loaded-overlay slot is freed. */
void func_02018aa4(void) {
    func_0205d89c(2);
    func_02017e60();
}
