#include "types.h"
extern void nds_vprintf(void *arg0, u32 fmtAddr, u32 val);

void nds_printf(void *arg0, u32 fmt, ...)
{
    u32 ap = (((u32)&fmt) & ~3u) + 4;
    nds_vprintf(arg0, fmt, ap);
}
