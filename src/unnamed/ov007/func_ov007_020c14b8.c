#include "types.h"

/* One of the texture records func_ov007_020b697c builds from the BMD
 * (func_ov007_020bd1c0 uploads them through func_ov007_020c14b8). Bit 0 of
 * flags: texel data to upload; bit 1: palette data. texDest / plttDest:
 * the VRAM slot each upload landed in. */
struct Tex {
    u32 flags;
    int pad4;
    const void *texSrc; /* 0x08 */
    u32 texSize;
    u32 texDest;
    char pad_14[8];
    const void *plttSrc; /* 0x1c */
    u32 plttSize;
    u32 plttDest;
};

extern u32 data_ov007_02104bdc;
extern u32 data_ov007_02104be4;
extern void Crash(void);
extern void _ZN2GX12BeginLoadTexEv(void);
extern void _ZN2GX7LoadTexEPKvjj(const void *src, u32 slot, u32 size);
extern void _ZN2GX10EndLoadTexEv(void);
extern u32 data_ov007_02104be8;
extern u32 data_ov007_02104be0;
void BeginLoadTexPltt(void);
extern void _ZN2GX11LoadTexPlttEPKvjj(const void *src, u32 slot, u32 size);
extern void _ZN2GX14EndLoadTexPlttEv(void);

void func_ov007_020c1560(struct Tex *t) {
    u32 slot;
    u32 end;

    if (!(t->flags & 1))
        return;

    slot = data_ov007_02104bdc;
    end = data_ov007_02104be4;

    if (slot + t->texSize <= end) {
        _ZN2GX12BeginLoadTexEv();
        _ZN2GX7LoadTexEPKvjj(t->texSrc, data_ov007_02104bdc, t->texSize);
        _ZN2GX10EndLoadTexEv();

        t->texDest = data_ov007_02104bdc;
        data_ov007_02104bdc += t->texSize;
    } else {
        Crash();
    }
}

void func_ov007_020c14d4(struct Tex *t) {
    u32 slot;
    u32 end;

    if (!(t->flags & 2))
        return;

    slot = data_ov007_02104be8;
    end = data_ov007_02104be0;

    if (slot + t->plttSize <= end) {
        BeginLoadTexPltt();
        _ZN2GX11LoadTexPlttEPKvjj(t->plttSrc, data_ov007_02104be8, t->plttSize);
        _ZN2GX14EndLoadTexPlttEv();

        t->plttDest = data_ov007_02104be8;
        data_ov007_02104be8 += t->plttSize;
    } else {
        Crash();
    }
}

void func_ov007_020c14b8(void *t) {
    func_ov007_020c1560(t);
    func_ov007_020c14d4(t);
}
