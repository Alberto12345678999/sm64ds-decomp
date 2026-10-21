//cpp
#include "dScEntry_c.h"
extern "C" {
int func_0203da9c();
u32 func_02012790(u32 sound);
extern u16 data_020a0e5a[];
}

int dScEntry_c::CheckMenuConfirm(int player) {
    u16 pressed;
    if (player >= 0)
        pressed = data_020a0e5a[player * 2];
    else
        pressed = data_020a0e5a[func_0203da9c() * 2];
    if (pressed != 0) {
        if (pressed & 0xc)
            return 1;
        func_02012790(0xe);
    }
    return 0;
}
