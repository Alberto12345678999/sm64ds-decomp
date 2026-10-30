#include "nitro/spi/pm.h"

/* PMi_WaitBusy by shape: spin until the channel is released. */
void func_0205ff08(void)
{
    int *p = &data_020a8114.lock;
    while (*(volatile int *)p != 0) {
    }
}
