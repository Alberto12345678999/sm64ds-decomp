//cpp
/* CP15 coprocessor primitives, 0x0206da64..0x0206dab4.
   Second CP15 run: three unnamed p15 primitives plus the two MPU region-7
   methods, not contiguous with the 0x02058bb0 body in CP15.cpp. The cstd tail
   run begins at func_0206dab4, so this run is its own file. Whole-function asm
   is emitted in source order; compiled bodies are too, under a per-function
   defer_codegen off. */
#include "types.h"

extern "C" {
// HAND-ASM PRIMITIVE: byte-faithful asm-block match. This function was assembly
// in the original (SDK/runtime primitive: block copy, matrix/math, CP15, context
// switch, etc.), so there is no C to decompile it to -- the asm block is the
// faithful source. Counts as matched (asm-primitive policy), not a C transcription.
// @symbol func_0206da64
asm int func_0206da64(void) {
    mov r0, #1
    b lbl
    mov r0, #0
    b lbl
lbl:
    mrc p15, 0, r1, c1, c0, 0
    and r2, r1, #1
    tst r0, r0
    biceq r1, r1, #1
    orrne r1, r1, #1
    mcr p15, 0, r1, c1, c0, 0
    mov r0, r2
    bx lr
}

// HAND-ASM PRIMITIVE: byte-faithful asm-block match. This function was assembly
// in the original (SDK/runtime primitive: block copy, matrix/math, CP15, context
// switch, etc.), so there is no C to decompile it to -- the asm block is the
// faithful source. Counts as matched (asm-primitive policy), not a C transcription.
// @symbol func_0206da94
asm void func_0206da94(void) { mrc p15, 0, r0, c7, c10, 1; bx lr }

// HAND-ASM PRIMITIVE: byte-faithful asm-block match. This function was assembly
// in the original (SDK/runtime primitive: block copy, matrix/math, CP15, context
// switch, etc.), so there is no C to decompile it to -- the asm block is the
// faithful source. Counts as matched (asm-primitive policy), not a C transcription.
// @symbol func_0206da9c
asm void func_0206da9c(void) { mrc p15, 0, r0, c7, c6, 1; bx lr }
}

#pragma push
#pragma defer_codegen off
// @symbol _ZN4CP1517MPUGetDataRegion7Ev
/* CP15::MPUGetDataRegion7() at 0x0206daa4 -- read back MPU data region 7.
 *
 * HAND-ASM PRIMITIVE: `mrc`/`mcr p15` are coprocessor accesses and no C
 * construct compiles to them, so the asm block is the faithful source rather
 * than a transcription of something lost. The asm-primitive policy is unchanged
 * by this migration; what changes is only that the compiler mangles the symbol
 * instead of the file spelling it by hand. Layout-free (plan phase 1): no
 * `this`, no vtable, no struct, no includers. */
namespace CP15 {

unsigned int MPUGetDataRegion7(void)
{
    unsigned int v;
    asm { mrc p15,0,v,c6,c7,0 }
    return v;
}

}
#pragma pop

#pragma push
#pragma defer_codegen off
// @symbol _ZN4CP1514MPUDataRegion7Ej
/* CP15::MPUDataRegion7(u32) at 0x0206daac -- write MPU data region 7 (c6,c7).
 *
 * HAND-ASM PRIMITIVE: `mrc`/`mcr p15` are coprocessor accesses and no C
 * construct compiles to them, so the asm block is the faithful source rather
 * than a transcription of something lost. The asm-primitive policy is unchanged
 * by this migration; what changes is only that the compiler mangles the symbol
 * instead of the file spelling it by hand. Layout-free (plan phase 1): no
 * `this`, no vtable, no struct, no includers. */
namespace CP15 {

void MPUDataRegion7(unsigned int x)
{
    asm { mcr p15,0,x,c6,c7,0 }
}

}
#pragma pop
