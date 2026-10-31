#include "types.h"
#include "WmWork.h"
extern char* data_020a9db4;
extern int func_02068e44(int parentMaxSize, int childMaxSize, int maxEntry);

/* Set the MP sizes and the parent's maxEntry. Refused (0) once the wireless
   layer is initialized, or if func_02068e44 rejects them. The game's link
   setup func_0203e20c passes (0x1fe, 8, 3). */
int func_02068dc8(int parentMaxSize, int childMaxSize, int maxEntry) {
    if (WM_WORK->initialized)
        return 0;
    if (func_02068e44(parentMaxSize, childMaxSize, maxEntry) == 0)
        return 0;
    WM_WORK->parentParam.maxEntry = maxEntry;
    WM_WORK->parentMaxSize = parentMaxSize;
    WM_WORK->childMaxSize = childMaxSize;
    return 1;
}
