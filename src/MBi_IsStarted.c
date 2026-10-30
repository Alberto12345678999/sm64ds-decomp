#include "WmWork.h"
extern char *data_020a9db4;

/* NitroSDK MBi_IsStarted (mb_wm.c): whether the wireless layer is up: WmWork.initialized == 1, set after
   WM_Initialize. func_02067928 refuses to register a file before then. */
int MBi_IsStarted(void) {
    return WM_WORK->initialized == 1;
}
