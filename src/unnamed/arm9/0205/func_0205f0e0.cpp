//cpp
#include "types.h"
#include "IRQ.h"
#include "nitro/spi/tp.h"

extern "C" {

extern TPWork data_020a80cc;

void func_0205f0e0(s16 *arg)
{
    u32 state;
    unsigned long long vv;

    if (arg == 0) {
        data_020a80cc.mCalibrated = 0;
        return;
    }

    state = IRQ::Disable();

    vv = (u32)arg[2];
    *(volatile u16 *)0x4000280 = 0;
    *(volatile u32 *)0x4000290 = 0x10000000;
    *(volatile unsigned long long *)0x4000298 = vv;
    data_020a80cc.mCalibration[0] = arg[0];
    data_020a80cc.mCalibration[1] = arg[2];
    while (*(volatile u16 *)0x4000280 & 0x8000) {
    }

    data_020a80cc.mCalibration[2] = *(volatile u32 *)0x40002a0;
    vv = (u32)arg[3];
    *(volatile u16 *)0x4000280 = 0;
    *(volatile u32 *)0x4000290 = 0x10000000;
    *(volatile unsigned long long *)0x4000298 = vv;
    data_020a80cc.mCalibration[3] = arg[1];
    data_020a80cc.mCalibration[4] = arg[3];
    while (*(volatile u16 *)0x4000280 & 0x8000) {
    }
    data_020a80cc.mCalibration[5] = *(volatile u32 *)0x40002a0;

    IRQ::Restore(state);
    data_020a80cc.mCalibrated = 1;
}
}
