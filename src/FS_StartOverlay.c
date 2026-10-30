/* NitroSDK FS_overlay.c FS_StartOverlay: once an overlay's image is in RAM,
 * a multiboot child (the halfword at 0x027ffc40 reads 2) checks the digest of
 * an overlay flagged authenticated (FSi_CompareDigest against its 20-byte
 * entry at data_0209a7ec), clearing the image and crashing on failure; then
 * the image is decompressed in place when flagged compressed
 * (MIi_UncompressBackward, given the end of the compressed image), and its
 * static initializers run from sinit_init to sinit_init_end. This SDK has no
 * DC_FlushRange step. */
#include "nitro/fs/overlay.h"

extern int FSi_CompareDigest(char *spec_digest, void *src, int len);
extern void func_0205a588(void *dst, int value, int size);
extern void Crash(void);
extern void MIi_UncompressBackward(void *bottom);

extern char data_0209aff8[];
extern char data_0209a7ec[];

void FS_StartOverlay(FSOverlayInfo *p_ovi) {
    unsigned char flags = p_ovi->header.flag;
    unsigned int rare_size;
    if (flags & 1) {
        rare_size = p_ovi->header.compressed;
    } else {
        rare_size = p_ovi->header.ram_size;
    }
    if (*(unsigned short *)0x27ffc40 == 2) {
        int ret = 0;
        if (flags & 2) {
            int odt_max = (int)(data_0209aff8 - data_0209a7ec) / 20;
            if (p_ovi->header.id < (unsigned int)odt_max) {
                char *spec_digest = data_0209a7ec + p_ovi->header.id * 0x14;
                ret = FSi_CompareDigest(spec_digest, p_ovi->header.ram_address, rare_size);
            }
        }
        if (ret == 0) {
            func_0205a588(p_ovi->header.ram_address, 0, rare_size);
            Crash();
            return;
        }
    }
    if (p_ovi->header.flag & 1) {
        MIi_UncompressBackward(p_ovi->header.ram_address + rare_size);
    }
    {
        FSOverlayInitFunc *p = p_ovi->header.sinit_init;
        FSOverlayInitFunc *q = p_ovi->header.sinit_init_end;
        while (p < q) {
            FSOverlayInitFunc fn = *p;
            if (fn != 0)
                fn();
            p++;
        }
    }
}
