#include "WmWork.h"
extern char *data_020a9db4;
/* WmWork.parentMaxSize, the parent's MP send size (set by func_02068dc8).
   func_02066a94 uses it to size the request record it clears for a child. */
int func_0206881c(void) {
    return WM_WORK->parentMaxSize;
}
