#include "nitro/hw/registers.h"

extern void func_020190b8(void);
extern unsigned char data_0208ee00;

/* Set POWCNT1 bit 3 (geometry engine) and bit 2 (rendering engine) and raise
   the flag func_02019018 reads. func_020190b8 runs first, while the flag
   still holds the old state. Disable3dEngines is the inverse. */
void Enable3dEngines(void) {
    func_020190b8();
    REG_POWCNT1 |= 8;
    REG_POWCNT1 |= 4;
    data_0208ee00 = 1;
}
