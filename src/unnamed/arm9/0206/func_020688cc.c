#include "WmWork.h"
extern char *data_020a9db4;
/* parentParam.ggid[1], which the beacon senders pass to WM_SetGameInfo. */
int func_020688cc(void) {
    return WM_WORK->parentParam.ggid[1];
}
