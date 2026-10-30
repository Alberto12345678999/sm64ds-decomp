#include "nitro/spi/pm.h"

int func_0205ff20(int a, int b, int c);
void func_0205f8b0(int param);

/* Sends PM command 0x66 with a completion callback (see nitro/spi/pm.h). */
int func_0205f5fc(int a, int b, int c) {
    if (!func_0205ff20(a, b, c)) return 1;
    data_020a8114.callback = (PMCallback)b;
    data_020a8114.callbackArg = (void *)c;
    func_0205f8b0((a & 0xff) | 0x3006600);
    return 0;
}
