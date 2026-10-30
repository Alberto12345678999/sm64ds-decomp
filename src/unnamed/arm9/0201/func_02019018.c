#include "nitro/hw/registers.h"

extern void func_020190b8(void);
extern unsigned char data_0208ee00;

/* The inverse of Enable3dEngines: run func_020190b8 while the flag still
   reads 1, then clear POWCNT1 bit 3 (geometry engine) and bit 2 (rendering
   engine) and drop the flag. */
void Disable3dEngines(void) {
    func_020190b8();
    REG_POWCNT1 &= ~8;
    REG_POWCNT1 &= ~4;
    data_0208ee00 = 0;
}

/* Whether the 3D engines are on: the flag Enable3dEngines sets and
   Disable3dEngines clears. func_020190b8 tests it. */
int func_02019018(void) {
    return data_0208ee00;
}
