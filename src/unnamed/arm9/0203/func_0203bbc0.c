extern void func_0205f270(void);
extern void func_0205f1e4(void *p);
extern void func_0205f0e0(void *p);
extern void func_0205edd8(int a, int b);
extern void func_0205ea10(int mask);
extern int func_0205e9fc(int mask);
extern void Crash(void);
extern void func_0205eeac(int a, int b, void *p, int d);
extern void *data_020a0de0;
extern void *data_020a0df8;

/* Touch-panel setup at boot (func_0201a054). The callees sit in the
   address order of the NitroSDK TP library as pret's pokediamond SPI_tp.s
   lays it out, which names them: TP_Init (func_0205f270), TP_GetUserInfo
   and TP_SetCalibrateParam on the calibration data_020a0de0, then
   func_0205edd8(3, 30), most likely TP_RequestSetStability by its
   arguments and its command flag (8), then
   TP_RequestAutoSamplingStartAsync (func_0205eeac) at V-count 0, four
   samples a frame, into the nine-entry ring data_020a0df8 that
   func_0203b9bc reads. Each request is waited out (TP_WaitBusy,
   func_0205ea10) and an error (TP_CheckError, func_0205e9fc) crashes. */
void func_0203bbc0(void)
{
    func_0205f270();
    func_0205f1e4(&data_020a0de0);
    func_0205f0e0(&data_020a0de0);
    func_0205edd8(3, 0x1e);
    func_0205ea10(8);
    if (func_0205e9fc(8) != 0)
        Crash();
    func_0205eeac(0, 4, &data_020a0df8, 9);
    func_0205ea10(2);
    if (func_0205e9fc(2) != 0)
        Crash();
}
