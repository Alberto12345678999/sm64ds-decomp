extern void _ZN8dScene_c22ResetHardwareRegistersEv(void);
void SetBankForBG(int);
/* local extern: C file cannot include GX.h. */
extern void LoadBG1Char(const void *p, unsigned int a, unsigned int b);
/* local extern: C file cannot include GX.h. */
extern void LoadBGPltt(const void *p, unsigned int a, unsigned int b);
extern void ResetCrashScreen(void);
extern void ShowCrashScreen(void);
/* local extern: C file cannot include GX.h. */
extern void DispOn(void);
extern char data_0208a178;
extern char data_0208c178;

void InitCrashScreen(void)
{
    _ZN8dScene_c22ResetHardwareRegistersEv();
    *(volatile short *)0x4000050 = 0;
    *(volatile short *)0x4001050 = 0;
    SetBankForBG(8);
    *(volatile int *)0x4000000 = (*(volatile int *)0x4000000 & ~0x1f00) | 0x200;
    *(volatile short *)0x400000a = (unsigned short)((*(volatile unsigned short *)0x400000a & 0x43) | 0x1e10);
    LoadBG1Char(&data_0208a178, 0, 0x2000);
    *(volatile short *)0x5000000 = 0x7c00;
    LoadBGPltt(&data_0208c178, 0x1a0, 0x60);
    ResetCrashScreen();
    ShowCrashScreen();
    DispOn();
    *(volatile int *)0x4001000 = *(volatile int *)0x4001000 & ~0x10000;
}
