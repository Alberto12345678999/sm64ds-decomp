#include "WmWork.h"
extern char *data_020a9db4;

/* Whether the wireless layer is up: WmWork.initialized == 1, set after
   WM_Initialize. func_02067928 refuses to register a file before then. */
int func_020687f8(void) {
    return WM_WORK->initialized == 1;
}
