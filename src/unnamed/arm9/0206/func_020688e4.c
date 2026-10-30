#include "WmWork.h"
extern char *data_020a9db4;
/* parentParam.ggid[0], which the beacon senders pass to WM_SetGameInfo. */
int func_020688e4(void) {
    return WM_WORK->parentParam.ggid[0];
}
