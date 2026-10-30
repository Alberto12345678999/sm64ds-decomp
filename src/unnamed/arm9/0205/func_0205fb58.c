#include "types.h"
#include "nitro/spi/pm.h"
extern int func_0205ff20(int a, int b, int c, int d);
extern void func_0205f8b0(int param);

/* PMi_ReadRegisterAsync by shape: claim the channel, arm read slot `a` with
   buffer `b`, and send command 0x65 for register `a`. */
int func_0205fb58(int a, int b, int c, int d)
{
    int z;
    if (!func_0205ff20(a, b, c, d))
        return 1;
    z = 0;
    data_020a8138[a].flag = (u16)z;
    data_020a8114.callback = (PMCallback)c;
    data_020a8114.callbackArg = (void *)d;
    data_020a8138[a].arg = b;
    func_0205f8b0((a & 0xff) | 0x3006500);
    return z;
}
