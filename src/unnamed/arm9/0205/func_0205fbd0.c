#include "nitro/spi/pm.h"

int func_0205ff20(int a, int b, int c);
void func_0205f8b0(int param);

/* PM_SendUtilityCommandAsync by shape: claim the channel and send command
   0x63 in two PXI words, the high and low halves of `a`. */
int func_0205fbd0(int a, int b, int c) {
    if (!func_0205ff20(a, b, c)) return 1;
    data_020a8114.callback = (PMCallback)b;
    data_020a8114.callbackArg = (void *)c;
    func_0205f8b0((int)(((unsigned int)a >> 0x10) & 0xff) | 0x2006300);
    func_0205f8b0((a & 0xffff) | 0x1010000);
    return 0;
}
