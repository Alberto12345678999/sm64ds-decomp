/* MI_SetWramBank (the Nitro SDK's mi_wram.c): select which CPU owns the
 * shared WRAM blocks. OS_Init passes 3 (MI_WRAM_ARM7_ALL). */
#include "nitro/hw/registers.h"

void MI_SetWramBank(int cnt) {
    REG_WRAMCNT = cnt;
}
