/* NitroSDK OSi_CommonCallback (os_reset.c): the OS PXI channel callback.
 * The ARM7's answer to OS_PXI_COMMAND_RESET sets OSi_IsResetOccurred, which
 * OS_ResetSystem spins on; any other command stops the system. */
#include "types.h"

#define OS_PXI_COMMAND_MASK 0x00007f00
#define OS_PXI_COMMAND_SHIFT 8
#define OS_PXI_COMMAND_RESET 0x10

extern void Crash(void); /* OS_Terminate */

extern vu16 OSi_IsResetOccurred;

void OSi_CommonCallback(int tag, u32 data, int err) {
    u16 command = (u16)((data & OS_PXI_COMMAND_MASK) >> OS_PXI_COMMAND_SHIFT);
    if (command == OS_PXI_COMMAND_RESET) {
        OSi_IsResetOccurred = 1;
        return;
    }
    Crash();
}
