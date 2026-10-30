#include "types.h"
extern int WMi_CheckInitialized(void);
extern int WM_CheckStateEx(int a, int b);
extern void func_0206116c(void);
extern void PXI_SetFifoRecvCallback(int tag, void *callback);

extern int data_020a89ac;
extern u16 data_020a89a8;

int func_02061674(void)
{
    int r;
    if (WMi_CheckInitialized() != 0)
        return 3;
    r = WM_CheckStateEx(1, 0);
    if (r != 0)
        return r;
    func_0206116c();
    PXI_SetFifoRecvCallback(0xa, 0);
    data_020a89ac = 0;
    data_020a89a8 = 0;
    return 0;
}
