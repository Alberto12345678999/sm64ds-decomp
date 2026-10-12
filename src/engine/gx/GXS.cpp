/* GXS/GX/G2/G2S/G2x/G3X/G3i -- the graphics register-writer run
 * (arm9 .text 0x02053abc..0x02056870, one original file).
 *
 * ida-hole-classification #2: one TU, no foreign class -- GX/GXS bank and mode
 * writers, the G2/G2S BG base-pointer readers, the G2x blend/affine writers,
 * the G3X fog/clear-color writers and the G3i geometry writers are one
 * contiguous run, with the address-named bank/matrix helpers between them.
 * GX/GXS/G2/G2S/G2x/G3X/G3i are namespaces, not classes: no this, no vtable,
 * no layout. GX:: members that lie inside the stretch are defined here too,
 * in ROM order like everything else.
 *
 * At 0x020553c0..0x02055454 sits func_020553c0, a HAND-ASM PRIMITIVE
 * (32 identical no-writeback stmia to the address in r0, a FIFO
 * port flush no C compiler emits; cf. CP15's in-TU asm primitives). It is
 * part of this run and owned here as a whole-function asm block under
 * `#pragma cplusplus off/on` (the shard's bytes verbatim, flat C symbol);
 * asm blocks emit in source order, matching the ascending layout.
 *
 * Definitions run ROM-ascending (GXS::SetGraphicsMode first) because
 * `#pragma defer_codegen off` makes mwccarm emit .text in source order;
 * the @symbol roster ties each one back to its ROM address.
 *
 * GX::LoadOBJ and func_020565b4 (the two constant-based VRAM destinations,
 * 0x6400000/0x6600000) were built under opt_propagation off, scoped per body
 * with push/pop (which binds because defer_codegen is off); every other
 * member matches with the default on.
 *
 * data_020a6088 is one u16 array at file scope (BSS, defined nowhere in
 * C). The shards viewed it as a u16 scalar, a u16 array, or a VramReg /
 * GXState overlay; scalar and array spellings of one symbol cannot
 * coexist in a TU even in separate bodies, so the scalar users reach it
 * through the array (&x becomes x, x = x | bits becomes x[0]) and the
 * struct views as array indices at the same offsets. Same addresses,
 * same widths, verified per function.
 * Shared single-spelling globals and DMA/callee externs are unified below,
 * spelled to match the callee definitions. The helpers keep their address
 * names under extern "C" (no recovered name exists).
 *
 * func_02054430 calls Vram__Map with two arguments against a one-parameter
 * definition (its shard spelled a private two-parameter extern). The call is
 * kept through a cast to the two-parameter function type: same two argument
 * registers, same direct branch, same return register.
 *
 * leftovers:
 * - Matrix2x2 is defined TU-locally: G2x.h forward-declares it and no
 *   shared header owns the layout.
 */


#include "types.h"
#include "G2x.h"
#include "G3X.h"
#include "G3i.h"
#include "math/Matrix.h"
#include "nitro/hw/registers.h"

#pragma defer_codegen off

struct Matrix2x2 { int m[4]; };

struct S { unsigned short flags; unsigned short pad;
               short val; };

/* GX sub-screen extended palette VRAM bases */
#define GXS_OBJ_EXT_PLTT_BASE 0x068a0000u
#define GXS_BG_EXT_PLTT_BASE  0x06898000u

extern u16 data_02099fcc;
extern u16 data_020a6084;
extern u16 data_020a608a;
extern u16 data_020a608c;
extern u16 data_020a608e;
extern u16 data_020a6090;
extern u16 data_020a6092;
extern u16 data_020a6094;
extern u16 data_020a6096;
extern u16 data_020a6098;
extern u16 data_020a609a;
extern u16 data_020a609c;
extern u16 data_020a609e;
extern u16 data_020a60a0;
extern u16 data_020a6088[];
extern int data_02099fd0;
extern u32 data_020a60a4;
extern u32 data_020a60a8;

extern "C" {
extern void func_020553c0(unsigned addr);
extern int func_02055490(int *out);
extern int func_02055464(int *out);
extern void DMASyncFillTransfer(unsigned int channel, void *dst, unsigned int data,
                                unsigned int size);
extern void MultiStore_Int(int val, int *dst, int len);
extern void func_0205a064(unsigned int ch, unsigned int src, unsigned int dst,
                          unsigned int size, void (*cb)(unsigned int), unsigned int cbArg);
extern void Copy32Bytes(void *src, void *dst);
extern void Copy36Bytes(int *src, int *dst);
extern void Copy48BytesFixed(int *src, int *dst);
extern void func_02059fa8(int ch);
extern void func_02059fd0(int ch, int src, int dst, u32 size, void (*cb)(int), int cbarg);
extern void DMASyncWordTransfer(u32 ch, const void *src, void *dst, u32 size);
extern void DMASyncHalfTransfer(u32 ch, const void *src, volatile void *dst, u32 count);
extern void MultiCopyHalf(const void *src, volatile void *dst, int count);
extern void MultiCopy_Int(int *src, int *dst, int len);
extern void Vram__Map(int mask);
extern u16 DisableVramBanks(u16 *bankBitsPtr);
extern u16 func_020541b8(u16 *bankBitsPtr);
extern int func_02053e4c(int x);
extern void func_02053d9c(void);
extern void func_02055624(void);
extern void func_02055780(void);
extern void func_020556d0(void);
extern void func_020554bc(void);
extern u16 func_020540f0(void);
extern u16 func_02054118(void);
extern void NormalizeVec3(Vector3 *v, Vector3 *out);
extern void CrossVec3(const Vector3 *a, const Vector3 *b, Vector3 *out);
extern Fix12i DotVec3(const Vector3 *a, const Vector3 *b);
extern int _ZN4cstd4fdivEii(int, int);
extern int _ZN4cstd11fdiv_resultEv(void);
extern s64 _ZN4cstd11ldiv_resultEv(void);
extern unsigned int _ZN3G2S13GetBG3CharPtrEv(void);
extern unsigned int _ZN3G2S13GetBG2CharPtrEv(void);
extern unsigned int _ZN3G2S13GetBG1CharPtrEv(void);
extern unsigned int _ZN3G2S13GetBG0CharPtrEv(void);
extern void *_ZN2G213GetBG2CharPtrEv(void);
extern int func_02054d88(void);
extern void *func_02054ea8(void);
extern void *func_02054efc(void);
extern unsigned int _ZN3G2S12GetBG3ScrPtrEv(void);
extern void *_ZN2G212GetBG3ScrPtrEv(void);
extern unsigned int _ZN3G2S12GetBG2ScrPtrEv(void);
extern void *_ZN2G212GetBG2ScrPtrEv(void);
extern unsigned int _ZN3G2S12GetBG1ScrPtrEv(void);
extern void *_ZN2G212GetBG1ScrPtrEv(void);
extern unsigned int _ZN3G2S12GetBG0ScrPtrEv(void);
extern void *_ZN2G212GetBG0ScrPtrEv(void);
extern void _ZN2GX22SetBankForSubBGExtPlttEt(u32 bank);
extern void _ZN2GX23SetBankForSubOBJExtPlttEt(u32 bank);
}


namespace GXS {
// @symbol _ZN3GXS15SetGraphicsModeEi
void SetGraphicsMode(int mode){
    *(volatile unsigned*)0x4001000 = (*(volatile unsigned*)0x4001000 & ~7) | mode;
}
}


namespace GX {
// @symbol _ZN2GX15SetGraphicsModeEiii
void SetGraphicsMode(int a, int b, int c){
 u16 t = data_02099fcc;
 unsigned reg = *(volatile unsigned*)0x4000000;
 data_020a6084 = (u16)a;
 if(t==0) a=0;
 reg = (unsigned)b | ((reg & 0xfff0fff0) | ((unsigned)a<<16));
 reg = ((unsigned)c<<3) | reg;
 *(volatile unsigned*)0x4000000 = reg;
 if(data_020a6084==0) data_02099fcc=0;
}
}


namespace GX {
// @symbol _ZN2GX6DispOnEv
void DispOn(){
 data_02099fcc = 1;
 u16 t = data_020a6084;
 if(t!=0){
   volatile unsigned *r = (volatile unsigned*)0x4000000;
   *r = (*r & ~0x30000u) | ((unsigned)t<<16);
   return;
 }
 *(volatile unsigned*)0x4000000 |= 0x10000;
}
}


// @symbol func_02053b98
extern "C" void func_02053b98(void){
  unsigned v = *(volatile unsigned*)0x4000000;
  data_02099fcc = 0;
  data_020a6084 = (unsigned short)((v & 0x30000) >> 0x10);
  *(volatile unsigned*)0x4000000 = v & ~0x30000;
}


// @symbol func_02053be0
extern "C" int func_02053be0(int enable) {
    volatile unsigned short *reg = (volatile unsigned short *)0x4000004;
    int old = *reg & 8;
    if (enable) {
        *reg |= 8;
    } else {
        *reg &= ~8;
    }
    return old;
}


// @symbol func_02053c10
extern "C" int func_02053c10(int enable) {
    volatile unsigned short *reg = (volatile unsigned short *)0x4000004;
    int old = *reg & 0x10;
    if (enable) {
        *reg |= 0x10;
    } else {
        *reg &= ~0x10;
    }
    return old;
}


// @symbol func_02053c40
extern "C" void func_02053c40(void)
{
    void DMASyncFillTransfer(int a0, int a1, int a2, int a3);
    *(volatile unsigned short *)0x4000304 |= 0x8000;
    *(volatile unsigned short *)0x4000304 =
        (*(volatile unsigned short *)0x4000304 & 0xfffffdf1) | 0x20e;
    *(volatile unsigned short *)0x4000304 |= 1;
    func_02053d9c();
    *(volatile unsigned short *)0x4000004 = 0;
    *(volatile int *)0x4000000 = 0;
    if ((&data_02099fd0)[0] != -1) {
        DMASyncFillTransfer((&data_02099fd0)[0], 0x4000008, 0, 0x60);
        *(volatile unsigned short *)0x400006c = 0;
        DMASyncFillTransfer((&data_02099fd0)[0], 0x4001000, 0, 0x70);
    } else {
        volatile int a = 0;
        volatile int b;
        MultiStore_Int(a, (int *)0x4000008, 0x60);
        *(volatile unsigned short *)0x400006c = 0;
        b = 0;
        MultiStore_Int(b, (int *)0x4001000, 0x70);
    }
    *(volatile unsigned short *)0x4000020 = 0x100;
    *(volatile unsigned short *)0x4000026 = 0x100;
    *(volatile unsigned short *)0x4000030 = 0x100;
    *(volatile unsigned short *)0x4000036 = 0x100;
    *(volatile unsigned short *)0x4001020 = 0x100;
    *(volatile unsigned short *)0x4001026 = 0x100;
    *(volatile unsigned short *)0x4001030 = 0x100;
    *(volatile unsigned short *)0x4001036 = 0x100;
}


// @symbol func_02053d9c
extern "C" void func_02053d9c(void)
{
    data_020a6088[0] = 0;
    data_020a6088[1] = 0;
    data_020a6088[2] = 0;
    data_020a6088[3] = 0;
    data_020a6088[4] = 0;
    data_020a6088[5] = 0;
    data_020a6088[6] = 0;
    data_020a6088[7] = 0;
    data_020a6088[8] = 0;
    data_020a6088[9] = 0;
    data_020a6088[10] = 0;
    data_020a6088[11] = 0;
    data_020a6088[12] = 0;
    *(volatile unsigned int *)0x4000240 = 0;
    *(volatile unsigned char *)0x4000244 = 0;
    *(volatile unsigned char *)0x4000245 = 0;
    *(volatile unsigned char *)0x4000246 = 0;
    *(volatile unsigned short *)0x4000248 = 0;
}


// @symbol func_02053e1c
extern "C" void func_02053e1c(void) {
    (void)func_02053e4c(*(unsigned short *)((char *)&data_020a6088 + 0xa));
}


// @symbol func_02053e34
extern "C" void func_02053e34(void) {
    (void)func_02053e4c(*(unsigned short *)((char *)&data_020a6088 + 8));
}


// @symbol func_02053e4c
extern "C" int func_02053e4c(int x) {
    int r = 0;
    if (x & 0x1)   r += 0x20000;
    if (x & 0x2)   r += 0x20000;
    if (x & 0x4)   r += 0x20000;
    if (x & 0x8)   r += 0x20000;
    if (x & 0x10)  r += 0x10000;
    if (x & 0x20)  r += 0x4000;
    if (x & 0x40)  r += 0x4000;
    if (x & 0x80)  r += 0x8000;
    if (x & 0x100) r += 0x4000;
    return r;
}


// @symbol func_02053ea0
extern "C" int func_02053ea0(void) { return data_020a6088[10]; }


// @symbol func_02053eb0
extern "C" int func_02053eb0(void) { return data_020a6088[9]; }


// @symbol func_02053ec0
extern "C" int func_02053ec0(void) { return data_020a6088[5]; }


// @symbol func_02053ed0
extern "C" int func_02053ed0(void) { return data_020a6088[4]; }


// @symbol func_02053ee0
/* func_02053ee0 @ 0x02053ee0 -- clear OBJ ext-palette enable bit in sub-engine
 * DISPCNT, then disable the VRAM bank assignment via DisableVramBanks. */
extern "C" u16 func_02053ee0(void) {
    *(vu32 *)0x04001000 &= ~0x80000000;
    return DisableVramBanks(&data_020a60a0);
}


// @symbol func_02053f08
/* func_02053f08 @ 0x02053f08 -- clear BG ext-palette enable bit in sub-engine
 * DISPCNT, then disable the VRAM bank assignment via DisableVramBanks. */
extern "C" u16 func_02053f08(void) {
    REG_DISPCNT_SUB &= ~DISPLAY_CONTROL_BG_EXT_PALETTE;
    return DisableVramBanks(&data_020a609e);
}


// @symbol func_02053f30
extern "C" u16 func_02053f30(void) {
    return DisableVramBanks(&data_020a609c);
}


// @symbol func_02053f44
extern "C" u16 func_02053f44(void) {
    return DisableVramBanks(&data_020a609a);
}


// @symbol func_02053f58
extern "C" u16 func_02053f58(void) {
    return DisableVramBanks(data_020a6088);
}


// @symbol func_02053f6c
extern "C" u16 func_02053f6c(void) {
    return DisableVramBanks(&data_020a608e);
}


// @symbol func_02053f80
extern "C" u16 func_02053f80(void) {
    return DisableVramBanks(&data_020a6094);
}


// @symbol func_02053f94
extern "C" u16 func_02053f94(void) {
    return DisableVramBanks(&data_020a6092);
}


// @symbol func_02053fa8
extern "C" u16 func_02053fa8(void) {
    return DisableVramBanks(&data_020a6090);
}


// @symbol func_02053fbc
/* func_02053fbc @ 0x02053fbc -- clear OBJ ext-palette enable bit in main-engine
 * DISPCNT, then disable the VRAM bank assignment via DisableVramBanks. */
extern "C" u16 func_02053fbc(void) {
    *(vu32 *)0x04000000 &= ~0x80000000;
    return DisableVramBanks(&data_020a6098);
}


// @symbol func_02053fe0
/* func_02053fe0 @ 0x02053fe0 -- clear BG ext-palette enable bit in main-engine
 * DISPCNT, then disable the VRAM bank assignment via DisableVramBanks. */
extern "C" u16 func_02053fe0(void) {
    *(vu32 *)0x04000000 &= ~0x40000000;
    return DisableVramBanks(&data_020a6096);
}


// @symbol func_02054004
extern "C" u16 func_02054004(void) {
    return DisableVramBanks(&data_020a608c);
}


// @symbol func_02054018
extern "C" u16 func_02054018(void) {
    return DisableVramBanks(&data_020a608a);
}


// @symbol DisableVramBanks
extern "C" unsigned short DisableVramBanks(unsigned short *r0)
{
    unsigned short flags = *r0;
    *r0 = 0;
    if (flags & 1)     *(volatile unsigned char *)0x4000240 = 0;
    if (flags & 2)     *(volatile unsigned char *)0x4000241 = 0;
    if (flags & 4)     *(volatile unsigned char *)0x4000242 = 0;
    if (flags & 8)     *(volatile unsigned char *)0x4000243 = 0;
    if (flags & 0x10)  *(volatile unsigned char *)0x4000244 = 0;
    if (flags & 0x20)  *(volatile unsigned char *)0x4000245 = 0;
    if (flags & 0x40)  *(volatile unsigned char *)0x4000246 = 0;
    if (flags & 0x80)  *(volatile unsigned char *)0x4000248 = 0;
    if (flags & 0x100) *(volatile unsigned char *)0x4000249 = 0;
    return flags;
}


// @symbol func_020540f0
/* func_020540f0 @ 0x020540f0 -- clear OBJ ext-palette enable bit in sub-engine
 * DISPCNT, then unmap the VRAM bank back to LCDC via func_020541b8. */
extern "C" u16 func_020540f0(void) {
    *(vu32 *)0x04001000 &= ~0x80000000;
    return func_020541b8(&data_020a60a0);
}


// @symbol func_02054118
/* func_02054118 @ 0x02054118 -- clear BG ext-palette enable bit in sub-engine
 * DISPCNT, then unmap the VRAM bank back to LCDC via func_020541b8. */
extern "C" u16 func_02054118(void) {
    *(vu32 *)0x04001000 &= ~0x40000000;
    return func_020541b8(&data_020a609e);
}


// @symbol func_02054140
extern "C" u16 func_02054140(void) {
    return func_020541b8(&data_020a609c);
}


// @symbol func_02054154
extern "C" u16 func_02054154(void) {
    return func_020541b8(&data_020a609a);
}


// @symbol func_02054168
extern "C" u16 func_02054168(void) {
    return func_020541b8(&data_020a6092);
}


// @symbol func_0205417c
extern "C" u16 func_0205417c(void) {
    return func_020541b8(&data_020a6090);
}


// @symbol func_02054190
extern "C" u16 func_02054190(void) {
    return func_020541b8(&data_020a608c);
}


// @symbol func_020541a4
extern "C" u16 func_020541a4(void) {
    return func_020541b8(&data_020a608a);
}


// @symbol func_020541b8
/* func_020541b8 at 0x020541b8
 * Takes a pointer to a VRAM bank bits field, clears it, merges bits into
 * the global VRAM register, then calls Vram__Map with those bits.
 * Returns the original bits value.
 */
extern "C" u16 func_020541b8(u16 *bankBitsPtr)
{
    u16 bits;
    bits = *bankBitsPtr;
    *bankBitsPtr = 0;
    data_020a6088[0] = data_020a6088[0] | bits;
    Vram__Map(bits);
    return bits;
}


namespace GX {
// @symbol _ZN2GX23SetBankForSubOBJExtPlttEt
void SetBankForSubOBJExtPltt(u16 x){
    data_020a6088[0] = (data_020a6088[0] | data_020a6088[12]) & ~x;
    data_020a6088[12] = x;
    if (x != 0) { if (x == 0x100) { *(volatile unsigned int*)0x4001000 |= 0x80000000; *(volatile unsigned char*)0x4000249 = 0x83; } }
    else { *(volatile unsigned int*)0x4001000 &= ~0x80000000; }
    Vram__Map(data_020a6088[0]);
}
}


namespace GX {
// @symbol _ZN2GX22SetBankForSubBGExtPlttEt
void SetBankForSubBGExtPltt(u16 x){
    data_020a6088[0] = (data_020a6088[0] | data_020a6088[11]) & ~x;
    data_020a6088[11] = x;
    if (x != 0) { if (x == 0x80) { *(volatile unsigned int*)0x4001000 |= 0x40000000; *(volatile unsigned char*)0x4000248 = 0x82; } }
    else { *(volatile unsigned int*)0x4001000 &= ~0x40000000; }
    Vram__Map(data_020a6088[0]);
}
}


namespace GX {
// @symbol _ZN2GX16SetBankForSubOBJEt
void SetBankForSubOBJ(u16 x){
    data_020a6088[0] = (data_020a6088[0] | data_020a6088[10]) & ~x;
    data_020a6088[10] = x;
    switch (x) {
    case 0: break;
    case 8: *(volatile unsigned char*)0x4000243 = 0x84; break;
    case 0x100: *(volatile unsigned char*)0x4000249 = 0x82; break;
    }
    Vram__Map(data_020a6088[0]);
}
}


namespace GX {
// @symbol _ZN2GX15SetBankForSubBGEt
void SetBankForSubBG(u16 x){
  int s = (int) x;
  int new_var;
  unsigned int notx = ~((unsigned int) x);
  u16 old = data_020a6088[9];
  new_var = notx & (data_020a6088[0] | old);
  data_020a6088[9] = x;
  data_020a6088[0] = new_var;
  if (s <= 0x80)
  {
    if (s >= 0x80)
    {
      goto sub248;
    }
    else
      if (((s <= 4) && (s >= 0)) && (s != 0))
    {
      if (s == 4)
      {
        *((volatile unsigned char *) 0x4000242) = 0x84;
      }
    }
  }
  else
    if (s == 0x180)
  {
    *((volatile unsigned char *) 0x4000249) = 0x81;
    goto sub248;
  }
  goto done;
  sub248:
  *((volatile unsigned char *) 0x4000248) = 0x81;
  done:
  Vram__Map(data_020a6088[0]);
}
}


// @symbol func_02054430
extern "C" int func_02054430(int arg)
{
    unsigned short *p = data_020a6088;
    *p |= arg;
    // Two-argument call against the one-parameter definition (the
    // shard spelled a private two-parameter extern). Same argument
    // registers, same direct branch, same return register.
    return ((int (*)(int, unsigned short *))Vram__Map)(arg, p);
}


namespace GX {
// @symbol _ZN2GX17SetBankForTexPlttEt
void SetBankForTexPltt(u16 x){
    data_020a6088[0] = ~x & (data_020a6088[0] | data_020a6088[5]);
    data_020a6088[5] = x;
    switch (x) {
    case 0x40:
        *(volatile unsigned char*)0x4000246 = 0x83;
        break;
    case 0x60:
        *(volatile unsigned char*)0x4000246 = 0x8b;
    case 0x20:
        *(volatile unsigned char*)0x4000245 = 0x83;
        break;
    case 0x70:
        *(volatile unsigned char*)0x4000246 = 0x9b;
    case 0x30:
        *(volatile unsigned char*)0x4000245 = 0x93;
    case 0x10:
        *(volatile unsigned char*)0x4000244 = 0x83;
    case 0:
        break;
    }
    Vram__Map(data_020a6088[0]);
}
}


namespace GX {
// @symbol _ZN2GX13SetBankForTexEt
void SetBankForTex(u16 tex)
{
    data_020a6088[0] = (u16)(~tex & (data_020a6088[0] | data_020a6088[4]));
    data_020a6088[4] = tex;
    if (tex == 0) {
        *(volatile u16 *)0x4000060 &= 0xcffe;
    } else {
        *(volatile u16 *)0x4000060 =
            (u16)((*(volatile u16 *)0x4000060 & ~0x3000) | 1);
        switch (tex) {
        case 0:
            break;
        case 5:
            *(volatile u8 *)0x4000240 = 0x83;
            *(volatile u8 *)0x4000242 = 0x8b;
            break;
        case 9:
            *(volatile u8 *)0x4000240 = 0x83;
            *(volatile u8 *)0x4000243 = 0x8b;
            break;
        case 10:
            *(volatile u8 *)0x4000241 = 0x83;
            *(volatile u8 *)0x4000243 = 0x8b;
            break;
        case 11:
            *(volatile u8 *)0x4000240 = 0x83;
            *(volatile u8 *)0x4000241 = 0x8b;
            *(volatile u8 *)0x4000243 = 0x93;
            break;
        case 13:
            *(volatile u8 *)0x4000240 = 0x83;
            *(volatile u8 *)0x4000242 = 0x8b;
            *(volatile u8 *)0x4000243 = 0x93;
            break;
        case 8:
            *(volatile u8 *)0x4000243 = 0x83;
            break;
        case 12:
            *(volatile u8 *)0x4000243 = 0x8b;
            // fallthrough
        case 4:
            *(volatile u8 *)0x4000242 = 0x83;
            break;
        case 14:
            *(volatile u8 *)0x4000243 = 0x93;
            // fallthrough
        case 6:
            *(volatile u8 *)0x4000242 = 0x8b;
            // fallthrough
        case 2:
            *(volatile u8 *)0x4000241 = 0x83;
            break;
        case 15:
            *(volatile u8 *)0x4000243 = 0x9b;
            // fallthrough
        case 7:
            *(volatile u8 *)0x4000242 = 0x93;
            // fallthrough
        case 3:
            *(volatile u8 *)0x4000241 = 0x8b;
            // fallthrough
        case 1:
            *(volatile u8 *)0x4000240 = 0x83;
            break;
        }
    }
    Vram__Map(data_020a6088[0]);
}
}


// @symbol func_02054748
extern "C" void func_02054748(int x)
{
    data_020a6088[0] = (u16)((data_020a6088[0] | data_020a6088[7]) & ~x);
    data_020a6088[7] = (u16)x;
    switch (x) {
    case 0:
        *(volatile unsigned int *)0x4000000 &= ~0x40000000;
        break;
    case 0x10:
        *(volatile unsigned int *)0x4000000 |= 0x40000000;
        *(volatile unsigned char *)0x4000244 = 0x84;
        break;
    case 0x40:
        *(volatile unsigned int *)0x4000000 |= 0x40000000;
        *(volatile unsigned char *)0x4000246 = 0x8c;
        break;
    case 0x60:
        *(volatile unsigned char *)0x4000246 = 0x8c;
        // fallthrough
    case 0x20:
        *(volatile unsigned char *)0x4000245 = 0x84;
        *(volatile unsigned int *)0x4000000 |= 0x40000000;
        break;
    }
    Vram__Map(data_020a6088[0]);
}


namespace GX {
// @symbol _ZN2GX13SetBankForOBJEt
void SetBankForOBJ(u16 obj)
{
    data_020a6088[0] = (u16)((data_020a6088[0] | data_020a6088[2]) & ~obj);
    data_020a6088[2] = obj;
    switch (obj) {
    case 0x00:
        break;
    case 0x03:
        *(volatile u8 *)0x4000241 = 0x8a;
        // fallthrough
    case 0x01:
        *(volatile u8 *)0x4000240 = 0x82;
        break;
    case 0x02:
        *(volatile u8 *)0x4000241 = 0x82;
        break;
    case 0x70:
        *(volatile u8 *)0x4000246 = 0x9a;
        // fallthrough
    case 0x30:
        *(volatile u8 *)0x4000245 = 0x92;
        // fallthrough
    case 0x10:
        *(volatile u8 *)0x4000244 = 0x82;
        break;
    case 0x50:
        *(volatile u8 *)0x4000246 = 0x92;
        *(volatile u8 *)0x4000244 = 0x82;
        break;
    case 0x60:
        *(volatile u8 *)0x4000246 = 0x8a;
        // fallthrough
    case 0x20:
        *(volatile u8 *)0x4000245 = 0x82;
        break;
    case 0x40:
        *(volatile u8 *)0x4000246 = 0x82;
        break;
    }
    Vram__Map(data_020a6088[0]);
}
}


namespace GX {
// @symbol _ZN2GX12SetBankForBGEt
void SetBankForBG(u16 bank)
{
    data_020a6088[0] = (u16)((data_020a6088[0] | data_020a6088[1]) & ~bank);
    data_020a6088[1] = bank;
    switch (bank) {
    case 0x00:
        break;
    case 0x08:
        *(volatile u8 *)0x4000243 = 0x81;
        break;
    case 0x0C:
        *(volatile u8 *)0x4000243 = 0x89;
        // fallthrough
    case 0x04:
        *(volatile u8 *)0x4000242 = 0x81;
        break;
    case 0x0E:
        *(volatile u8 *)0x4000243 = 0x91;
        // fallthrough
    case 0x06:
        *(volatile u8 *)0x4000242 = 0x89;
        // fallthrough
    case 0x02:
        *(volatile u8 *)0x4000241 = 0x81;
        break;
    case 0x0F:
        *(volatile u8 *)0x4000243 = 0x99;
        // fallthrough
    case 0x07:
        *(volatile u8 *)0x4000242 = 0x91;
        // fallthrough
    case 0x03:
        *(volatile u8 *)0x4000241 = 0x89;
        // fallthrough
    case 0x01:
        *(volatile u8 *)0x4000240 = 0x81;
        break;
    case 0x0B:
        *(volatile u8 *)0x4000240 = 0x81;
        *(volatile u8 *)0x4000241 = 0x89;
        *(volatile u8 *)0x4000243 = 0x91;
        break;
    case 0x0D:
        *(volatile u8 *)0x4000243 = 0x91;
        // fallthrough
    case 0x05:
        *(volatile u8 *)0x4000240 = 0x81;
        *(volatile u8 *)0x4000242 = 0x89;
        break;
    case 0x09:
        *(volatile u8 *)0x4000240 = 0x81;
        *(volatile u8 *)0x4000243 = 0x89;
        break;
    case 0x0A:
        *(volatile u8 *)0x4000241 = 0x81;
        *(volatile u8 *)0x4000243 = 0x89;
        break;
    case 0x70:
        *(volatile u8 *)0x4000246 = 0x99;
        // fallthrough
    case 0x30:
        *(volatile u8 *)0x4000245 = 0x91;
        // fallthrough
    case 0x10:
        *(volatile u8 *)0x4000244 = 0x81;
        break;
    case 0x50:
        *(volatile u8 *)0x4000246 = 0x91;
        *(volatile u8 *)0x4000244 = 0x81;
        break;
    case 0x60:
        *(volatile u8 *)0x4000246 = 0x89;
        // fallthrough
    case 0x20:
        *(volatile u8 *)0x4000245 = 0x81;
        break;
    case 0x40:
        *(volatile u8 *)0x4000246 = 0x81;
        break;
    }
    Vram__Map(data_020a6088[0]);
}
}


// @symbol Vram__Map
extern "C" void Vram__Map(int mask)
{
    if (mask & 0x1)   *(volatile unsigned char*)0x4000240 = 0x80;
    if (mask & 0x2)   *(volatile unsigned char*)0x4000241 = 0x80;
    if (mask & 0x4)   *(volatile unsigned char*)0x4000242 = 0x80;
    if (mask & 0x8)   *(volatile unsigned char*)0x4000243 = 0x80;
    if (mask & 0x10)  *(volatile unsigned char*)0x4000244 = 0x80;
    if (mask & 0x20)  *(volatile unsigned char*)0x4000245 = 0x80;
    if (mask & 0x40)  *(volatile unsigned char*)0x4000246 = 0x80;
    if (mask & 0x80)  *(volatile unsigned char*)0x4000248 = 0x80;
    if (mask & 0x100) *(volatile unsigned char*)0x4000249 = 0x80;
}


namespace G2S {
// @symbol _ZN3G2S13GetBG3CharPtrEv
unsigned int GetBG3CharPtr()
{
    int cfg = *(volatile int *)0x4001000;
    unsigned int v = *(volatile unsigned short *)0x400100e;
    int m = cfg & 7;
    if (m >= 3) {
        if (m >= 6) goto zero;
        if (v & 0x80) goto zero;
    }
    return (((v & 0x3c) >> 2) << 0xe) + 0x6200000;
zero:
    return 0;
}
}


// @symbol func_02054d88
extern "C" {
int func_02054d88(void)
{
    unsigned int mode = *(volatile unsigned int *)0x4000000 & 7;
    unsigned short h = *(volatile unsigned short *)0x400000e;
    if ((int)mode < 3 || ((int)mode < 6 && !(h & 0x80))) {
        unsigned int v = *(volatile unsigned int *)0x4000000;
        return 0x6000000 + (((v & 0x7000000) >> 0x18) << 0x10) + (((unsigned int)(h & 0x3c) >> 2) << 14);
    }
    return 0;
}
}


namespace G2S {
// @symbol _ZN3G2S13GetBG2CharPtrEv
unsigned GetBG2CharPtr()
{
  int v1 = *(volatile int*)0x4001000;
  unsigned short v2 = *(volatile unsigned short*)0x400100c;
  if (!((v1 & 7) >= 5 && (v2 & 0x80)))
    return ((unsigned)(v2 & 0x3c) >> 2 << 0xe) + 0x6200000;
  return 0;
}
}


namespace G2 {
// @symbol _ZN2G213GetBG2CharPtrEv
void*  GetBG2CharPtr(void)
{
  int mode = *(volatile unsigned int*)0x4000000 & 7;
  unsigned int bg2cnt = *(volatile unsigned short*)0x400000c;
  if(mode < 5 || !(bg2cnt & 0x80))
    return (void*)(0x6000000
      + (((*(volatile unsigned int*)0x4000000 & 0x7000000) >> 0x18) << 0x10)
      + (((bg2cnt & 0x3c) >> 2) << 14));
  return (void*)0;
}
}


namespace G2S {
// @symbol _ZN3G2S13GetBG1CharPtrEv
unsigned int GetBG1CharPtr()
{
    int v = *(volatile unsigned short *)0x400100a;
    return (((v & 0x3c) >> 2) << 0xe) + 0x6200000;
}
}


// @symbol func_02054ea8
extern "C" {
void* func_02054ea8(void){
  int off = ((*(volatile unsigned short*)0x400000a) & 0x3c) >> 2;
  unsigned int sbase = (*(volatile unsigned int*)0x4000000) & 0x7000000;
  return (void*)(0x6000000 + ((sbase >> 0x18) << 0x10) + (off << 14));
}
}


namespace G2S {
// @symbol _ZN3G2S13GetBG0CharPtrEv
unsigned int GetBG0CharPtr()
{
    int v = *(volatile unsigned short *)0x4001008;
    return (((v & 0x3c) >> 2) << 0xe) + 0x6200000;
}
}


// @symbol func_02054efc
extern "C" {
void* func_02054efc(void){
  int off = ((*(volatile unsigned short*)0x4000008) & 0x3c) >> 2;
  unsigned int sbase = (*(volatile unsigned int*)0x4000000) & 0x7000000;
  return (void*)(0x6000000 + ((sbase >> 0x18) << 0x10) + (off << 14));
}
}


namespace G2S {
// @symbol _ZN3G2S12GetBG3ScrPtrEv
unsigned int GetBG3ScrPtr()
{
    int m = *(volatile int *)0x4001000 & 7;
    unsigned int v = *(volatile unsigned short *)0x400100e;
    unsigned int r1 = (v & 0x1f00) >> 8;
    switch (m) {
    case 0:
    case 1:
    case 2:
        return (r1 << 0xb) + 0x6200000;
    case 3:
    case 4:
    case 5:
        if (v & 0x80) return (r1 << 0xe) + 0x6200000;
        return (r1 << 0xb) + 0x6200000;
    case 6:
        return 0;
    default:
        return 0;
    }
}
}


namespace G2 {
// @symbol _ZN2G212GetBG3ScrPtrEv
void*  GetBG3ScrPtr()
{
  unsigned int mode = *(volatile unsigned int*)0x4000000 & 7;
  unsigned short bg3cnt = *(volatile unsigned short*)0x400000e;
  unsigned int sbase = ((*(volatile unsigned int*)0x4000000 & 0x38000000) >> 0x1b) << 0x10;
  unsigned int off = ((unsigned int)(bg3cnt & 0x1f00)) >> 8;
  switch(mode){
  case 0: case 1: case 2:
    return (void*)(0x6000000 + sbase + (off << 11));
  case 3: case 4: case 5:
    if(bg3cnt & 0x80) return (void*)(0x6000000 + (off << 0xe));
    return (void*)(0x6000000 + sbase + (off << 11));
  case 6:
    return (void*)0;
  default:
    return (void*)0;
  }
}
}


namespace G2S {
// @symbol _ZN3G2S12GetBG2ScrPtrEv
unsigned int GetBG2ScrPtr()
{
    int m = *(volatile int *)0x4001000 & 7;
    unsigned int v = *(volatile unsigned short *)0x400100c;
    unsigned int r1 = (v & 0x1f00) >> 8;
    switch (m) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return (r1 << 0xb) + 0x6200000;
    case 5:
        if (v & 0x80) return (r1 << 0xe) + 0x6200000;
        return (r1 << 0xb) + 0x6200000;
    case 6:
        return 0;
    default:
        return 0;
    }
}
}


namespace G2 {
// @symbol _ZN2G212GetBG2ScrPtrEv
void*  GetBG2ScrPtr(void)
{
  unsigned int mode = *(volatile unsigned int*)0x4000000 & 7;
  unsigned short bg2cnt = *(volatile unsigned short*)0x400000c;
  unsigned int sbase = ((*(volatile unsigned int*)0x4000000 & 0x38000000) >> 0x1b) << 0x10;
  unsigned int off = ((unsigned int)(bg2cnt & 0x1f00)) >> 8;
  switch(mode){
  case 0: case 1: case 2: case 3: case 4:
    return (void*)(0x6000000 + sbase + (off << 11));
  case 5:
    if(bg2cnt & 0x80) return (void*)(0x6000000 + (off << 0xe));
    return (void*)(0x6000000 + sbase + (off << 11));
  case 6:
    return (void*)0x6000000;
  default:
    return (void*)0;
  }
}
}


namespace G2S {
// @symbol _ZN3G2S12GetBG1ScrPtrEv
unsigned int GetBG1ScrPtr()
{
    int v = *(volatile unsigned short *)0x400100a;
    return (((v & 0x1f00) >> 8) << 0xb) + 0x6200000;
}
}


namespace G2 {
// @symbol _ZN2G212GetBG1ScrPtrEv
void*  GetBG1ScrPtr(void)
{
  int off = ((*(volatile unsigned short*)0x400000a) & 0x1f00) >> 8;
  unsigned int sbase = (*(volatile unsigned int*)0x4000000) & 0x38000000;
  return (void*)(0x6000000 + ((sbase >> 0x1b) << 0x10) + (off << 11));
}
}


namespace G2S {
// @symbol _ZN3G2S12GetBG0ScrPtrEv
unsigned int GetBG0ScrPtr()
{
    int v = *(volatile unsigned short *)0x4001008;
    return (((v & 0x1f00) >> 8) << 0xb) + 0x6200000;
}
}


namespace G2 {
// @symbol _ZN2G212GetBG0ScrPtrEv
void* GetBG0ScrPtr(void)
{
  int off = ((*(volatile unsigned short*)0x4000008) & 0x1f00) >> 8;
  unsigned int sbase = (*(volatile unsigned int*)0x4000000) & 0x38000000;
  return (void*)(0x6000000 + ((sbase >> 0x1b) << 0x10) + (off << 11));
}
}


// @symbol func_020551f0
extern "C" void func_020551f0(struct S* s, int v){
  unsigned short h = s->flags;
  if (v < 0) {
    if ((h & 0xc0) == 0x80) s->flags = (h & ~0xc0) | 0xc0;
    s->val = (short)(-v);
  } else {
    if ((h & 0xc0) == 0xc0) s->flags = (h & ~0xc0) | 0x80;
    s->val = (short)v;
  }
}


// @symbol _ZN3G2x18SetBlendBrightnessEPVtts
/* Writes the hardware brightness registers behind `p`. The SIGN of `amt`
 * selects the mode rather than a separate flag: negative sets bits 0xc0
 * (fade to black) and writes the magnitude, positive sets 0x80 (fade to
 * white) and writes the value as-is. So one signed argument carries both
 * "which way" and "how much". */
void G2x::SetBlendBrightness(volatile unsigned short *p, unsigned short val, short amt)
{
    if (amt < 0) {
        p[0] = val | 0xc0;
        p[2] = -amt;
    } else {
        p[0] = val | 0x80;
        p[2] = amt;
    }
}


// @symbol _ZN3G2x13SetBlendAlphaEPVttttj
/* The final argument is 32-bit: the ROM loads its stack slot with `ldr`, not
   `ldrh`. The former `...ttttt` name contradicted that instruction. */
void G2x::SetBlendAlpha(volatile u16 *reg, u16 firstTarget,
                        u16 secondTarget, u16 firstAlpha,
                        u32 secondAlpha)
{
    *(volatile u32 *)reg =
        ((firstTarget | 0x40) | (secondTarget << 8)) |
        ((firstAlpha | (secondAlpha << 8)) << 16);
}


// @symbol _ZN3G2x12SetBGyAffineEPVtP9Matrix2x2iiii
/* Loads a background's affine transform into the hardware registers behind `p`.
 *
 * The four matrix terms go out as TWO 32-bit writes, packed in pairs, each term
 * narrowed to s16 after a >> 4 -- the registers are 1.7.8 fixed point while the
 * matrix is 20.12, so the shift is the format conversion, not a scale.
 *
 * The reference point is the interesting part: dx/dy are the offset from (a,b)
 * to (c,d), and the displacement written is `m * d + (origin << 12)`. So the
 * caller gives a point to rotate ABOUT and a point to rotate TO, and this
 * resolves them into the single origin the hardware actually takes. */
void G2x::SetBGyAffine(volatile unsigned short *p, Matrix2x2 *m, int a, int b, int c, int d)
{
    u16 pa = (u16)(s16)(m->m[0] >> 4);
    u16 pb = (u16)(s16)(m->m[1] >> 4);
    *(volatile unsigned int *)p = pa | (pb << 16);
    u16 pc = (u16)(s16)(m->m[2] >> 4);
    u16 pd = (u16)(s16)(m->m[3] >> 4);
    *(volatile unsigned int *)(p + 2) = pc | (pd << 16);
    int dx = c - a;
    int dy = d - b;
    int x = m->m[0] * dx + m->m[1] * dy + (a << 12);
    int y = m->m[2] * dx + m->m[3] * dy + (b << 12);
    *(volatile int *)(p + 4) = x >> 4;
    *(volatile int *)(p + 6) = y >> 4;
}


// @symbol func_0205532c
extern "C" void func_0205532c(int *a, int *v)
{
    *(volatile unsigned int *)0x4000400 = 0x19;
    Copy36Bytes(a, (int *)0x4000400);
    *(volatile unsigned int *)0x4000400 = v[0];
    *(volatile unsigned int *)0x4000400 = v[1];
    *(volatile unsigned int *)0x4000400 = v[2];
}


// @symbol Geometry_MatrixMultiply3x3
extern "C" void Geometry_MatrixMultiply3x3(int *m)
{
    *(volatile unsigned int *)0x4000400 = 0x1a;
    Copy36Bytes(m, (int *)0x4000400);
}


// @symbol func_02055388
extern "C" void func_02055388(int *m)
{
    *(volatile unsigned int *)0x4000400 = 0x19;
    Copy48BytesFixed(m, (int *)0x4000400);
}


// @symbol func_020553a4
extern "C" void func_020553a4(int *m)
{
    *(volatile unsigned int *)0x4000400 = 0x17;
    Copy48BytesFixed(m, (int *)0x4000400);
}


// @symbol func_020553c0
#pragma cplusplus off
asm void func_020553c0(unsigned addr)
{
    mov r1, #0
    mov r2, #0
    mov r3, #0
    mov r12, #0
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    stmia r0, {r1, r2, r3, r12}
    bx lr
}
#pragma cplusplus on


// @symbol func_02055454
extern "C" void func_02055454(int v) { REG_BG0OFS = v; }


// @symbol func_02055464
extern "C" int func_02055464(int *out) {
    if (*(volatile unsigned int *)0x4000600 & 0x4000)
        return -1;
    *out = (*(volatile unsigned int *)0x4000600 & 0x2000) >> 13;
    return 0;
}


// @symbol func_02055490
extern "C" int func_02055490(int *out) {
    if (*(volatile unsigned int *)0x4000600 & 0x4000)
        return -1;
    *out = (*(volatile unsigned int *)0x4000600 & 0x1f00) >> 8;
    return 0;
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


// @symbol _ZN3G3X13SetClearColorEtiiib
void G3X::SetClearColor(unsigned short a, int b, int c, int d, bool e) {
    unsigned int v = (a | (b << 16)) | (d << 24);
    // Reads the whole bool slot as an int: the byte-proven widening form.
    if (*(int *)&e) v |= 0x8000;
    *(volatile unsigned int *)0x4000350 = v;
    *(volatile unsigned short *)0x4000354 = (unsigned short)c;
}


// @symbol func_020555a4
extern "C" void func_020555a4(void *dst) {
    MultiCopyHalf(dst, (void *)0x04000380, 0x40);
}


// @symbol _ZN3G3X11SetFogTableEPv
void G3X::SetFogTable(void *table) {
    Copy32Bytes(table, (void *)0x4000360);
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


// @symbol func_020556d0
extern "C" void func_020556d0(void)
{
    int a, b;
    *(volatile u32 *)0x4000600 |= 0x8000;
    while (func_02055490(&a)) ;
    while (func_02055464(&b)) ;
    *(volatile u32 *)0x4000440 = 3;
    *(volatile u32 *)0x4000454 = 0;
    *(volatile u32 *)0x4000440 = 0;
    if (b != 0) *(volatile u32 *)0x4000448 = b;
    *(volatile u32 *)0x4000454 = 0;
    *(volatile u32 *)0x4000440 = 2;
    *(volatile u32 *)0x4000448 = a;
    *(volatile u32 *)0x4000454 = 0;
}


// @symbol func_02055780
extern "C" void func_02055780(void)
{
    func_020553c0(0x4000400);
    while (*(volatile unsigned *)0x4000600 & 0x8000000)
        ;
}


// @symbol func_020557b4
extern "C" void func_020557b4(void)
{
    while (*(volatile unsigned int *)0x4000600 & 0x8000000);
    *(volatile unsigned int *)0x4000600 |= 0x8000;
    *(volatile unsigned short *)0x4000060 |= 0x2000;
    *(volatile unsigned short *)0x4000060 |= 0x1000;
    func_02055624();
    *(volatile unsigned int *)0x40004a4 = 0x1f0080;
    *(volatile unsigned int *)0x40004a8 = 0;
    *(volatile unsigned int *)0x40004ac = 0;
}


// @symbol func_0205583c
extern "C" void func_0205583c(void)
{
    func_02055780();
    *(volatile unsigned int *)0x4000504 = 0;
    while (*(volatile unsigned int *)0x4000600 & 0x8000000)
        ;
    *(volatile unsigned short *)0x4000060 = 0;
    *(volatile unsigned int *)0x4000600 = 0;
    *(volatile unsigned int *)0x4000010 = 0;
    *(volatile unsigned short *)0x4000060 |= 0x2000;
    *(volatile unsigned short *)0x4000060 |= 0x1000;
    *(volatile unsigned short *)0x4000060 &= ~0x3002;
    *(volatile unsigned short *)0x4000060 = (*(volatile unsigned short *)0x4000060 & ~0x3000) | 0x10;
    *(volatile unsigned short *)0x4000060 &= 0xcffb;
    *(volatile unsigned int *)0x4000600 |= 0x8000;
    *(volatile unsigned int *)0x4000600 = (*(volatile unsigned int *)0x4000600 & ~0xc0000000) | 0x80000000;
    func_020556d0();
    *(volatile unsigned int *)0x4000350 = 0;
    *(volatile unsigned short *)0x4000354 = 0x7fff;
    *(volatile unsigned short *)0x4000356 = 0;
    *(volatile unsigned int *)0x4000358 = 0;
    *(volatile unsigned short *)0x400035c = 0;
    *(volatile unsigned short *)0x4000008 &= ~3;
    func_020554bc();
    *(volatile unsigned int *)0x40004a4 = 0x1f0080;
    *(volatile unsigned int *)0x40004a8 = 0;
    *(volatile unsigned int *)0x40004ac = 0;
}


// @symbol func_02055998
extern "C" void func_02055998(int *m)
{
    *(volatile int *)0x4000440 = 3;
    *(volatile int *)0x4000458 = m[0] << 4;
    *(volatile int *)0x4000458 = m[1] << 4;
    *(volatile int *)0x4000458 = m[2] << 4;
    *(volatile int *)0x4000458 = m[3] << 4;
    *(volatile int *)0x4000458 = m[4] << 4;
    *(volatile int *)0x4000458 = m[5] << 4;
    *(volatile int *)0x4000458 = m[6] << 4;
    *(volatile int *)0x4000458 = m[7] << 4;
    *(volatile int *)0x4000458 = m[8] << 4;
    *(volatile int *)0x4000458 = m[9] << 4;
    *(volatile int *)0x4000458 = m[10] << 4;
    *(volatile int *)0x4000458 = m[11] << 4;
    *(volatile int *)0x4000458 = m[12];
    *(volatile int *)0x4000458 = m[13];
    *(volatile int *)0x4000458 = m[14];
    *(volatile int *)0x4000458 = m[15];
}


// @symbol _ZN3G3i7LookAt_EPK7Vector3S2_S2_bP9Matrix4x3
void G3i::LookAt_(const Vector3 *at, const Vector3 *up, const Vector3 *eye,
                  bool draw, Matrix4x3 *mat)
{
    Vector3 forward;
    Vector3 right;
    Vector3 up2;
    Fix12i tx;
    Fix12i ty;
    Fix12i tz;
    volatile int *mtx;
    forward.x = at->x - eye->x;
    forward.y = at->y - eye->y;
    forward.z = at->z - eye->z;
    NormalizeVec3(&forward, &forward);
    CrossVec3(up, &forward, &right);
    NormalizeVec3(&right, &right);
    CrossVec3(&forward, &right, &up2);
    if (draw) {
        *(volatile int *)0x4000440 = 2;
        mtx = (volatile int *)0x400045c;
        *mtx = right.x;
        *mtx = up2.x;
        *mtx = forward.x;
        *mtx = right.y;
        *mtx = up2.y;
        *mtx = forward.y;
        *mtx = right.z;
        *mtx = up2.z;
        *mtx = forward.z;
    }
    tx = -DotVec3(at, &right);
    ty = -DotVec3(at, &up2);
    tz = -DotVec3(at, &forward);
    if (draw) {
        *mtx = tx;
        *mtx = ty;
        *mtx = tz;
    }
    if (mat == 0) {
        return;
    }
    mat->r.m[0] = right.x;
    mat->r.m[1] = up2.x;
    mat->r.m[2] = forward.x;
    mat->r.m[3] = right.y;
    mat->r.m[4] = up2.y;
    mat->r.m[5] = forward.y;
    mat->r.m[6] = right.z;
    mat->r.m[7] = up2.z;
    mat->r.m[8] = forward.z;
    mat->t.x = tx;
    mat->t.y = ty;
    mat->t.z = tz;
}


// @symbol _ZN3G3i13PerspectiveW_E5Fix12IiES1_S1_S1_S1_S1_bP9Matrix4x3
#pragma cplusplus off
void _ZN3G3i13PerspectiveW_E5Fix12IiES1_S1_S1_S1_S1_bP9Matrix4x3(
    int sinF, int cosF, int aspect, int n, int f, int scaleW, int flag,
    int *mtx)
{
    int tmp;
    volatile int *port;
    int xx;
    s64 q;
    int zz;
    int v;
    int wz;
    tmp = _ZN4cstd4fdivEii(cosF, sinF);
    if (scaleW != 0x1000)
        tmp = tmp * scaleW / 0x1000;
    *(volatile u64 *)0x4000290 = (u64)(unsigned)tmp << 32;
    *(volatile u64 *)0x4000298 = (unsigned)aspect;
    if (flag) {
        *(volatile int *)0x4000440 = 0;
        port = (volatile int *)0x4000458;
    }
    if (mtx) {
        mtx[1] = 0;
        mtx[2] = 0;
        mtx[3] = 0;
        mtx[4] = 0;
        mtx[6] = 0;
        mtx[7] = 0;
        mtx[8] = 0;
        mtx[9] = 0;
        mtx[11] = -scaleW;
        mtx[12] = 0;
        mtx[13] = 0;
        mtx[15] = 0;
    }
    xx = _ZN4cstd11fdiv_resultEv();
    *(volatile u64 *)0x4000290 = (u64)0x1000 << 32;
    *(volatile u64 *)0x4000298 = (unsigned)(n - f);
    if (flag) {
        *port = xx;
        *port = 0;
        *port = 0;
        *port = 0;
        *port = 0;
        *port = tmp;
        *port = 0;
        *port = 0;
        *port = 0;
        *port = 0;
    }
    if (mtx) {
        mtx[0] = xx;
        mtx[5] = tmp;
    }
    q = _ZN4cstd11ldiv_resultEv();
    if (scaleW != 0x1000)
        q = q * scaleW / 0x1000;
    zz = (int)(((f + n) * q + 0x80000000LL) >> 32);
    v = (int)(((s64)(n << 1) * f + 0x800) >> 12);
    wz = (int)((q * v + 0x80000000LL) >> 32);
    if (flag) {
        *port = zz;
        *port = -scaleW;
        *port = 0;
        *port = 0;
        *port = wz;
        *port = 0;
    }
    if (mtx) {
        mtx[10] = zz;
        mtx[14] = wz;
    }
}
#pragma cplusplus on


namespace GXS {
// @symbol _ZN3GXS17EndLoadOBJExtPlttEv
void EndLoadOBJExtPltt() {
    u32 dmaId = data_02099fd0;
    if (dmaId != (u32)-1) {
        func_02059fa8(dmaId);
    }
    _ZN2GX23SetBankForSubOBJExtPlttEt(data_020a60a8);
    data_020a60a8 = 0;
}
}


namespace GXS {
// @symbol _ZN3GXS14LoadOBJExtPlttEPKvjj
void LoadOBJExtPltt(const void* src, u32 destSlotAddr, u32 size) {
    u32 dmaId = data_02099fd0;
    if (dmaId != (u32)-1) {
        func_02059fd0(dmaId, (int)src, (int)(destSlotAddr + GXS_OBJ_EXT_PLTT_BASE), size, 0, 0);
    } else {
        MultiCopy_Int((int*)src, (int*)(destSlotAddr + GXS_OBJ_EXT_PLTT_BASE), size);
    }
}
}


namespace GXS {
// @symbol _ZN3GXS19BeginLoadOBJExtPlttEv
void BeginLoadOBJExtPltt()
{
    data_020a60a8 = func_020540f0();
}
}


namespace GXS {
// @symbol _ZN3GXS16EndLoadBGExtPlttEv
void EndLoadBGExtPltt() {
    u32 dmaId = data_02099fd0;
    if (dmaId != (u32)-1) {
        func_02059fa8(dmaId);
    }
    _ZN2GX22SetBankForSubBGExtPlttEt(data_020a60a4);
    data_020a60a4 = 0;
}
}


namespace GXS {
// @symbol _ZN3GXS13LoadBGExtPlttEPKvjj
void LoadBGExtPltt(const void* src, u32 destSlotAddr, u32 size) {
    u32 dmaId = data_02099fd0;
    if (dmaId != (u32)-1) {
        func_02059fd0(dmaId, (int)src, (int)(destSlotAddr + GXS_BG_EXT_PLTT_BASE), size, 0, 0);
    } else {
        MultiCopy_Int((int*)src, (int*)(destSlotAddr + GXS_BG_EXT_PLTT_BASE), size);
    }
}
}


namespace GXS {
// @symbol _ZN3GXS18BeginLoadBGExtPlttEv
void BeginLoadBGExtPltt()
{
    data_020a60a4 = func_02054118();
}
}


// @symbol func_02055fb4
// Loads BG3 char data into SUB BG3 VRAM (G2S::GetBG3CharPtr).
extern "C" void func_02055fb4(const void *src, u32 offset, u32 size)
{
    void *charPtr = (void*)_ZN3G2S13GetBG3CharPtrEv();
    if (data_02099fd0 != (u32)-1)
        DMASyncWordTransfer(data_02099fd0, src, (char *)charPtr + offset, size);
    else
        MultiCopy_Int((int*)src, (int*)((char *)charPtr + offset), size);
}


// @symbol func_02056014
// Loads BG3 char data into MAIN BG3 VRAM (0x2054d88 getter).
extern "C" void func_02056014(const void *src, unsigned int offset, unsigned int count)
{
    void *base = (void*)func_02054d88();
    unsigned int channel = data_02099fd0;
    if (channel != (unsigned int)-1) {
        DMASyncWordTransfer(channel, src, (char *)base + offset, count);
    } else {
        MultiCopy_Int((int*)src, (int*)((char *)base + offset), count);
    }
}


// @symbol func_02056074
// Loads BG2 char data into SUB BG2 VRAM (G2S::GetBG2CharPtr).
extern "C" void func_02056074(const void *src, unsigned int offset, unsigned int count)
{
    void *base = (void*)_ZN3G2S13GetBG2CharPtrEv();
    unsigned int channel = data_02099fd0;
    if (channel != (unsigned int)-1) {
        DMASyncWordTransfer(channel, src, (char *)base + offset, count);
    } else {
        MultiCopy_Int((int*)src, (int*)((char *)base + offset), count);
    }
}


// @symbol func_020560d4
// Loads BG2 char data into MAIN BG2 VRAM (G2::GetBG2CharPtr).
extern "C" void func_020560d4(const void *src, u32 offset, u32 size)
{
    void *charPtr = _ZN2G213GetBG2CharPtrEv();
    if (data_02099fd0 != (u32)-1)
        DMASyncWordTransfer(data_02099fd0, src, (char *)charPtr + offset, size);
    else
        MultiCopy_Int((int*)src, (int*)((char *)charPtr + offset), size);
}


// Loads BG1 character data into SUB BG1 VRAM (G2S::GetBG1CharPtr).
namespace GXS {
// @symbol _ZN3GXS11LoadBG1CharEPKvjj
void LoadBG1Char(const void *src, unsigned int offset, unsigned int count){
    void *base = (void*)_ZN3G2S13GetBG1CharPtrEv();
    unsigned int channel = data_02099fd0;
    if (channel != (unsigned int)-1) {
        DMASyncWordTransfer(channel, src, (char *)base + offset, count);
    } else {
        MultiCopy_Int((int*)src, (int*)((char *)base + offset), count);
    }
}
}


// Loads character data into MAIN BG1 VRAM (G2::GetBG1CharPtr, 0x2054ea8).
namespace GX {
// @symbol _ZN2GX11LoadBG1CharEPKvjj
void LoadBG1Char(const void *src, unsigned int offset, unsigned int count){
    void *base = func_02054ea8();
    unsigned int channel = data_02099fd0;
    if (channel != (unsigned int)-1) {
        DMASyncWordTransfer(channel, src, (char *)base + offset, count);
    } else {
        MultiCopy_Int((int*)src, (int*)((char *)base + offset), count);
    }
}
}


// Loads BG0 character data into SUB BG0 VRAM (G2S::GetBG0CharPtr).
namespace GXS {
// @symbol _ZN3GXS11LoadBG0CharEPKvjj
void LoadBG0Char(const void *src, u32 offset, u32 size){
    void *charPtr = (void*)_ZN3G2S13GetBG0CharPtrEv();
    if (data_02099fd0 != (u32)-1)
        DMASyncWordTransfer(data_02099fd0, src, (char *)charPtr + offset, size);
    else
        MultiCopy_Int((int*)src, (int*)((char *)charPtr + offset), size);
}
}


// Loads character data into MAIN BG0 VRAM (G2::GetBG0CharPtr, 0x2054efc).
namespace GX {
// @symbol _ZN2GX11LoadBG0CharEPKvjj
void LoadBG0Char(const void *src, unsigned int offset, unsigned int count){
    void *base = func_02054efc();
    unsigned int channel = data_02099fd0;
    if (channel != (unsigned int)-1) {
        DMASyncWordTransfer(channel, src, (char *)base + offset, count);
    } else {
        MultiCopy_Int((int*)src, (int*)((char *)base + offset), count);
    }
}
}


// @symbol func_020562b4
// Loads BG3 screen data to the sub-engine plane (G2S::GetBG3ScrPtr).
extern "C" void func_020562b4(const void *src, u32 offset, u32 count)
{
    void *bgPtr;
    u32 ch;
    bgPtr = (void*)_ZN3G2S12GetBG3ScrPtrEv();
    ch = data_02099fd0;
    if (ch != (u32)~0)
        DMASyncHalfTransfer(ch, src, (char *)bgPtr + offset, count);
    else
        MultiCopyHalf(src, (char *)bgPtr + offset, count);
}


// @symbol func_02056314
// Loads BG3 screen data to the main-engine plane (G2::GetBG3ScrPtr).
extern "C" void func_02056314(void *dst, u32 offset, u32 len) {
    void *ip = _ZN2G212GetBG3ScrPtrEv();
    s32 chan = data_02099fd0;
    if (chan != -1) {
        DMASyncHalfTransfer(chan, dst, (char *)ip + offset, len);
    } else {
        MultiCopyHalf(dst, (char *)ip + offset, len);
    }
}


// @symbol func_02056374
// Loads BG2 screen data to the sub-engine plane (G2S::GetBG2ScrPtr).
extern "C" void func_02056374(const void *src, u32 offset, u32 count)
{
    void *bgPtr;
    u32 ch;
    bgPtr = (void*)_ZN3G2S12GetBG2ScrPtrEv();
    ch = data_02099fd0;
    if (ch != (u32)~0)
        DMASyncHalfTransfer(ch, src, (char *)bgPtr + offset, count);
    else
        MultiCopyHalf(src, (char *)bgPtr + offset, count);
}


// @symbol func_020563d4
// Loads BG2 screen data to the main-engine plane (G2::GetBG2ScrPtr).
extern "C" void func_020563d4(const void *src, u32 offset, u32 count)
{
    void *bgPtr;
    u32 ch;
    bgPtr = _ZN2G212GetBG2ScrPtrEv();
    ch = data_02099fd0;
    if (ch != (u32)~0)
        DMASyncHalfTransfer(ch, src, (char *)bgPtr + offset, count);
    else
        MultiCopyHalf(src, (char *)bgPtr + offset, count);
}


// @symbol func_02056434
// Loads BG1 screen data to the sub-engine plane (G2S::GetBG1ScrPtr).
extern "C" void func_02056434(const void* src, int offset, int count)
{
    volatile unsigned char* ptr = (volatile unsigned char*)_ZN3G2S12GetBG1ScrPtrEv();
    int ch = data_02099fd0;
    if (ch != -1)
    {
        DMASyncHalfTransfer(ch, src, ptr + offset, count);
    }
    else
    {
        MultiCopyHalf(src, ptr + offset, count);
    }
}


// @symbol func_02056494
// Loads BG1 screen data to the main-engine plane (G2::GetBG1ScrPtr).
extern "C" void func_02056494(const void* src, int offset, int count)
{
    volatile unsigned char* ptr = (volatile unsigned char*)_ZN2G212GetBG1ScrPtrEv();
    int ch = data_02099fd0;
    if (ch != -1)
    {
        DMASyncHalfTransfer(ch, src, ptr + offset, count);
    }
    else
    {
        MultiCopyHalf(src, ptr + offset, count);
    }
}


// @symbol func_020564f4
// Loads BG0 screen data to the sub-engine plane (G2S::GetBG0ScrPtr).
extern "C" void func_020564f4(const void* src, int offset, int count)
{
    volatile unsigned char* ptr = (volatile unsigned char*)_ZN3G2S12GetBG0ScrPtrEv();
    int ch = data_02099fd0;
    if (ch != -1)
    {
        DMASyncHalfTransfer(ch, src, ptr + offset, count);
    }
    else
    {
        MultiCopyHalf(src, ptr + offset, count);
    }
}


// @symbol func_02056554
// Loads BG0 screen data to the main-engine plane (G2::GetBG0ScrPtr).
extern "C" void func_02056554(const void* src, int offset, int count)
{
    volatile unsigned char* ptr = (volatile unsigned char*)_ZN2G212GetBG0ScrPtrEv();
    int ch = data_02099fd0;
    if (ch != -1)
    {
        DMASyncHalfTransfer(ch, src, ptr + offset, count);
    }
    else
    {
        MultiCopyHalf(src, ptr + offset, count);
    }
}


// @symbol func_020565b4
#pragma push
#pragma opt_propagation off
// Copies count words from src to VRAM address (0x6600000 + offset) -- sub
// OBJ VRAM. Same opt_propagation-off build as GX::LoadOBJ.
extern "C" void func_020565b4(const void *src, unsigned int offset, unsigned int count)
{
    unsigned int channel = data_02099fd0;
    unsigned int base = 0x6600000;
    if (channel != (unsigned int)-1) {
        DMASyncWordTransfer(channel, src, (void *)(base + offset), count);
    } else {
        MultiCopy_Int((int*)src, (int*)(base + offset), count);
    }
}
#pragma pop


#pragma push
#pragma opt_propagation off
// Copies count words from src to VRAM address (0x6400000 + offset) -- main
// OBJ VRAM. Needs opt_propagation off: the constant is kept out of the
// address arithmetic.
namespace GX {
// @symbol _ZN2GX7LoadOBJEPKvjj
void LoadOBJ(const void *src, unsigned int offset, unsigned int count){
    unsigned int channel = data_02099fd0;
    unsigned int base = 0x6400000;
    if (channel != (unsigned int)-1) {
        DMASyncWordTransfer(channel, src, (void *)(base + offset), count);
    } else {
        MultiCopy_Int((int*)src, (int*)(base + offset), count);
    }
}
#pragma pop
}


// @symbol func_02056674
// Copies count words from src to VRAM address (0x07000400 + offset) -- the
// sub-engine OAM block (ARM9 view). DMA channel if assigned, else CPU copy.
extern "C" void func_02056674(const void *src, unsigned int offset, unsigned int count)
{
    unsigned int channel = data_02099fd0;
    if (channel != (unsigned int)-1) {
        DMASyncWordTransfer(channel, src, (void *)(0x07000400 + offset), count);
    } else {
        MultiCopy_Int((int*)src, (int*)(0x07000400 + offset), count);
    }
}


// @symbol func_020566dc
// Copies count words from src to VRAM address (0x07000000 + offset) -- the
// main-engine OAM block (ARM9 view). DMA channel if assigned, else CPU copy.
extern "C" void func_020566dc(const void *src, unsigned int offset, unsigned int count)
{
    unsigned int channel = data_02099fd0;
    if (channel != (unsigned int)-1) {
        DMASyncWordTransfer(channel, src, (void *)(0x7000000 + offset), count);
    } else {
        MultiCopy_Int((int*)src, (int*)(0x7000000 + offset), count);
    }
}


// Loads OBJ palette data to sub-screen (GXS) palette VRAM at 0x05000600.
namespace GXS {
// @symbol _ZN3GXS11LoadOBJPlttEPKvjj
void LoadOBJPltt(const void* src, unsigned int offset, unsigned int size){
    int channel = data_02099fd0;
    if (channel != -1) {
        DMASyncHalfTransfer(channel, src, (void*)((char*)0x05000600 + offset), size);
    } else {
        MultiCopyHalf(src, (void*)((char*)0x05000600 + offset), size);
    }
}
}


// Loads OBJ palette data to main screen (GX) palette VRAM at 0x05000200.
namespace GX {
// @symbol _ZN2GX11LoadOBJPlttEPKvjj
void LoadOBJPltt(const void* src, unsigned int offset, unsigned int size){
    int channel = data_02099fd0;
    if (channel != -1) {
        DMASyncHalfTransfer(channel, src, (void*)((char*)0x05000200 + offset), size);
    } else {
        MultiCopyHalf(src, (void*)((char*)0x05000200 + offset), size);
    }
}
}


// Loads BG palette data to sub-screen (GXS) palette VRAM at 0x05000400.
namespace GXS {
// @symbol _ZN3GXS10LoadBGPlttEPKvjj
void LoadBGPltt(const void* src, unsigned int offset, unsigned int size){
    int channel = data_02099fd0;
    if (channel != -1) {
        DMASyncHalfTransfer(channel, src, (void*)((char*)0x05000400 + offset), size);
    } else {
        MultiCopyHalf(src, (void*)((char*)0x05000400 + offset), size);
    }
}
}
