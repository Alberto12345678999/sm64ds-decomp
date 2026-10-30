//cpp
#include "types.h"
#include "CP15.h"

extern "C" {

extern int WMi_CheckInitialized(void);
extern unsigned int *data_020a89ac;

int WM_CheckStateEx(int count, ...)
{
    int r;
    int *p;
    u16 target;
    r = WMi_CheckInitialized();
    if (r != 0)
        return r;
    CP15::InvalidateDataCache(data_020a89ac[1], 2);
    target = *(u16 *)data_020a89ac[1];
    p = (int *)((unsigned int)&count & ~3) + 1;
    r = 3;
    if (count == 0)
        return 3;
    do {
        p++;
        if (p[-1] == target)
            r = 0;
    } while (--count != 0);
    return r;
}
}
