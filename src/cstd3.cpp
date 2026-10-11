//cpp
/* arm9/cstd3 -- cstd::__assert plus the two card-wait register helpers at
 * .text 0x0206cd44..0x0206ce90, folded from three legacy shards. The division-
 * unit TU (arm9/cstd) and the square-root TU (arm9/cstd2) are elsewhere; this
 * run is bounded by func_0206ccd8 (the print helper __assert calls) ending at
 * 0x0206cd44 below and an undelinked ROM gap starting at 0x0206ce90 above.
 * Written in descending address order so reverse-source emission lands the
 * ROM-ascending run.
 */

extern "C" {
extern char data_020868a0;
extern char data_020868d4;
void func_0206ccd8(int first, ...);
int func_0206cf7c(int mask);
}

struct S {
    unsigned short f0;
    unsigned short f2;
    unsigned short f4;
};

extern "C" {
#pragma optimize_for_size on
// @symbol func_0206ce20
void func_0206ce20(struct S* s){
  unsigned short v = *(volatile unsigned short*)0x4000204;
  s->f0 = v;
  *(volatile unsigned short*)0x4000204 = (v & 0xffe3) | 0xf;
  if(func_0206cf7c(1) != 0){
    s->f4 = 1;
    s->f2 = *(volatile unsigned short*)0x27fff72;
    *(volatile unsigned short*)0x9fe2ffe = 0x20;
    *(volatile unsigned short*)0x27fff72 = 0x20;
  }
}
}

extern "C" {
#pragma optimize_for_size on
#pragma opt_common_subs off
// @symbol func_0206cd9c
void func_0206cd9c(struct S *s)
{
    volatile unsigned short scratch;

    if (func_0206cf7c(1) != 0 && s->f4 != 0) {
        volatile unsigned short *p27;
        volatile unsigned short *p9fe;
        unsigned short v2;

        p27 = (volatile unsigned short *)0x27fff72;
        p9fe = (volatile unsigned short *)0x9fe2ffe;
        v2 = s->f2;
        *p27 = v2;
        v2 = s->f2;
        *p9fe = v2;
        scratch = *(volatile unsigned short *)0x9fe20f0;
        scratch = *(volatile unsigned short *)0x9fe20f0;
        scratch = *(volatile unsigned short *)0x9fe20f0;
    }
    *(volatile unsigned short *)0x4000204 = s->f0;
}
}

namespace cstd {

void __builtin_trap();

// @symbol _ZN4cstd8__assertEPKcS1_S1_i
//
// cstd::__assert(const char*, const char*, const char*, int) at 0x0206cd44 --
// assertion failure path used by the game's cstd helpers. When `line` is
// non-zero, print with format data_020868a0 and trap forever; when zero,
// print with format data_020868d4 and return. Itanium substitution compresses
// the repeated `const char*` parameters to `EPKcS1_S1_i` (same pattern as
// cstd::strcmp's enrolled name).
void __assert(const char* file, const char* expr, const char* func, int line)
{
    if (line) {
        func_0206ccd8((int)&data_020868a0, file, expr, func);
        __builtin_trap();
        for (;;) {
        }
    } else {
        func_0206ccd8((int)&data_020868d4, file, expr, func);
    }
}

}
