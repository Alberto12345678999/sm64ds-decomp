#include "nitro/ctrdg/ctrdg_common.h"

extern CTRDGWork data_020a9de0; /* CTRDGi_Work */
extern void Crash(void);

void func_0206a694(int a0, int a1) {
    if ((a1 & 0x3f) == 1) {
        data_020a9de0.subpState = 1;
        return;
    }
    Crash();
}
