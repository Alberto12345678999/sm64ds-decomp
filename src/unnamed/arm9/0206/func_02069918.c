#include "types.h"
#include "WmWork.h"
extern char *data_020a9db4;

/* The port-1 receive callback func_020690b0 installs through
   WM_SetPortCallback. A successful callback with state 0x15 (PORT_RECV)
   goes to userCallback as event 9; the CONNECTED (7) and DISCONNECTED (9)
   tests ahead of it change nothing. */
void func_02069918(char *arg0)
{
    u16 v;
    if (*(u16 *)(arg0 + 2) != 0) return;
    v = *(u16 *)(arg0 + 4);
    if (v == 7) return;
    if (v == 9) return;
    if (v != 0x15) return;
    WM_WORK->userCallback(9, arg0);
}
