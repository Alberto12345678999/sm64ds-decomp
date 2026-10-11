//cpp
/* engine/gx/G3X.cpp — G3X TU (arm9 0x020554bc..0x020556d0)
 *
 * G3X is the 3D engine's fog and clear-color register writer set. All three
 * members are static (no this); func_020555a4 is a helper that uploads a
 * 32-entry (0x40-byte) toon table from a caller-built buffer to the
 * TOON_TABLE register block at 0x4000380 and keeps its func_ name under
 * extern "C". The run's two free helpers bracket the members: func_020554bc
 * (fog DMA/table fill) below and func_02055624 (geometry-engine FIFO drain)
 * above. Written ROM-descending because mwccarm emits .text in
 * reverse source order under deferred codegen.
 */
#include "G3X.h"

extern "C" {
void MultiCopyHalf(const void *src, void *dst, int size);
void Copy32Bytes(void *src, void *dst);
void func_020555a4(void *dst);
extern int data_02099fd0;
void func_0205a064(unsigned int ch, unsigned int src, unsigned int dst,
                   unsigned int size, void (*cb)(unsigned int), unsigned int cbArg);
void DMASyncFillTransfer(unsigned int channel, void *dst, unsigned int data,
                         unsigned int size);
void MultiStore_Int(int val, int *dst, int len);
extern int func_02055490(int *out);
extern int func_02055464(int *out);
}

// @symbol func_02055624
extern "C" void func_02055624(void)
{
    int a;
    int b;
    *(volatile unsigned int *)0x4000600 |= 0x8000;
    while (func_02055490(&a));
    while (func_02055464(&b));
    *(volatile unsigned int *)0x4000440 = 3;
    *(volatile unsigned int *)0x4000454 = 0;
    *(volatile unsigned int *)0x4000440 = 0;
    if (b != 0) *(volatile unsigned int *)0x4000448 = b;
    *(volatile unsigned int *)0x4000440 = 2;
    *(volatile unsigned int *)0x4000448 = a;
    *(volatile unsigned int *)0x4000454 = 0;
}

// @symbol _ZN3G3X6SetFogEbiii
void G3X::SetFog(bool enable, int a, int b, int c) {
    if (enable) {
        *(volatile unsigned short *)0x400035c = (unsigned short)c;
        *(volatile unsigned short *)0x4000060 =
            (b << 8) | (a << 6) | 0x80 | (*(volatile unsigned short *)0x4000060 & ~0x3f40);
    } else {
        *(volatile unsigned short *)0x4000060 = *(volatile unsigned short *)0x4000060 & 0xcf7f;
    }
}

// 0x4000360 is FOG_TABLE: 32 bytes, the whole table, copied from the caller's
// buffer in one go.
// @symbol _ZN3G3X11SetFogTableEPv
void G3X::SetFogTable(void *table) {
    Copy32Bytes(table, (void *)0x4000360);
}

// @symbol func_020555a4
extern "C" void func_020555a4(void *dst) {
    MultiCopyHalf(dst, (void *)0x04000380, 0x40);
}

// @symbol _ZN3G3X13SetClearColorEtiiib
void G3X::SetClearColor(unsigned short a, int b, int c, int d, bool e) {
    unsigned int v = (a | (b << 16)) | (d << 24);
    // Reads the whole bool slot as an int: the byte-proven widening form.
    if (*(int *)&e) v |= 0x8000;
    *(volatile unsigned int *)0x4000350 = v;
    *(volatile unsigned short *)0x4000354 = (unsigned short)c;
}

// @symbol func_020554bc
extern "C" void func_020554bc(void)
{
    int i;
    if ((&data_02099fd0)[0] != -1) {
        func_0205a064((&data_02099fd0)[0], 0x4000330, 0, 0x10, 0, 0);
        DMASyncFillTransfer((&data_02099fd0)[0], (void *)0x4000360, 0, 0x50);
    } else {
        volatile int a = 0;
        volatile int b;
        MultiStore_Int(a, (int*)0x4000330, 0x10);
        b = 0;
        MultiStore_Int(b, (int*)0x4000360, 0x50);
    }
    for (i = 0; i < 0x20; i++)
        *(volatile int*)0x40004d0 = 0;
}
