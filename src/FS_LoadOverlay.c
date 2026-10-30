#include "nitro/fs/overlay.h"
extern int func_02018b64(FSOverlayInfo *info);
extern void Crash(void);
extern void FS_StartOverlay(FSOverlayInfo *p_ovi);
extern void func_ov001_020aa420(void);

int FS_LoadOverlay(int proc, int id) {
    FSOverlayInfo info;
    unsigned int ram;
    unsigned int sum;
    if (!func_02018c00(&info, proc, id) || !func_02018b64(&info))
        return 0;
    ram = (unsigned int)info.header.ram_address;
    /* goto kept: an || guard around Crash() colours ram/sum differently (4 forms tried) */
    if (ram >= (unsigned int)func_ov001_020aa420) {
        sum = ram + info.header.ram_size;
        if (sum + info.header.bss_size <= 0x214eaa0u)
            goto start;
    }
    Crash();
start:
    FS_StartOverlay(&info);
    return 1;
}
