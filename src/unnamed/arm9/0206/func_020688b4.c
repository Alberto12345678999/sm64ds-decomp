#include "WmWork.h"
extern char *data_020a9db4;
/* parentParam.tgid, which the beacon senders pass to WM_SetGameInfo. */
int func_020688b4(void) {
    return WM_WORK->parentParam.tgid;
}
