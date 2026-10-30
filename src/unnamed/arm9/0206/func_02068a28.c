#include "types.h"
extern void func_020623ec(int a, int b, int c, int d, unsigned short e, unsigned short f);
/* Send on port 1 at priority 3: func_020623ec, which calls func_02062428
   with a null argument word in second place (NitroSDK WM_SetMPDataToPort's
   shape). The fourth parameter is unused. */
void func_02068a28(int a, int b, int c, int unused, u16 d)
{
    func_020623ec(a, b, c, d, 1, 3);
}
