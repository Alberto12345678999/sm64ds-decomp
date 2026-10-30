#include "nitro/fs/overlay.h"
extern void FS_InitFile(void *s);
extern int myFS_OpenFileDirect(void *s, int b, int c, int d, int e);
extern int myFS_ReadFile(void *s, void *b, int c);
extern int FS_CloseFile(void *self);
/* The ARM9 and ARM7 overlay tables when they are in memory: {address,
   length}, address 0 while not loaded. */
extern int data_020a8064[2];
extern int data_020a806c[2];
/* the archive func_02018cbc reads the table out of (FSArchive) */
extern int data_020a8074;
extern void CpuCopy8(void *dst, void *src, int n);

/* The card half of func_02018c00: read overlay table entry `shift` (0x20
   bytes) straight out of the ROM, the table offset and length coming from
   the header (a5/a6 for ARM9, a7/a8 for ARM7). 0 past the end. */
int func_02018cbc(FSOverlayInfo *info, int flag, int shift, int a3, int a5, int a6, int a7,
                  int a8) {
    char local[0x48];
    int off;
    int base;
    int hi;
    if (flag == 0) {
        hi = a6;
        base = a5;
    } else {
        hi = a8;
        base = a7;
    }
    off = shift << 5;
    if ((unsigned int)off >= (unsigned int)hi)
        return 0;
    FS_InitFile(local);
    myFS_OpenFileDirect(local, a3, base + off, base + hi, -1);
    myFS_ReadFile(local, &info->header, 0x20);
    FS_CloseFile(local);
    info->target = flag;
    return 1;
}

/* The game's copy of NitroSDK FS_LoadOverlayInfo(info, target, id), which
   LoadOverlay, UnloadOverlay, func_02017e94 and FS_LoadOverlay call: fill
   the 0x24-byte FSOverlayInfo with overlay `index`'s 0x20-byte table entry,
   then the target processor (0 ARM9, 1 ARM7) at +0x20. The entry comes from the
   in-memory table if there is one, else from the card, with the table's ROM
   offset and length from the cartridge header copy at 0x27ffe00 (+0x50 ARM9,
   +0x58 ARM7). 0 if index is past the table. */
int func_02018c00(FSOverlayInfo *info, int flag, int index) {
    int *base = (flag == 0) ? data_020a8064 : data_020a806c;
    int ptr = base[0];
    if (ptr != 0) {
        int off = index << 5;
        if ((unsigned int)off >= (unsigned int)base[1])
            return 0;
        CpuCopy8((void *)(ptr + off), &info->header, 0x20);
        info->target = flag;
        return 1;
    }
    {
        int *m = (int *)0x27ffe50;
        int *n = (int *)0x27ffe58;
        return func_02018cbc(info, flag, index, (int)&data_020a8074, m[0], m[1], n[0], n[1]);
    }
}
