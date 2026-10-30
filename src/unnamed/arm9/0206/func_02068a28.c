#include "types.h"
extern void WM_SetMPDataToPort(int a, int b, int c, int d, int e, int f);
/* Send on port 1 at priority 3 through WM_SetMPDataToPort, which calls
   WM_SetMPDataToPortEx with no callback argument. The fourth parameter is
   unused. */
void func_02068a28(int a, int b, int c, int unused, u16 d)
{
    WM_SetMPDataToPort(a, b, c, d, 1, 3);
}
