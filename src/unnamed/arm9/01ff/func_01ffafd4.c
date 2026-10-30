// HAND-ASM PRIMITIVE: byte-faithful asm-block match (assembly-only primitive). Per asm policy.
//
// func_01ffafd4 at 0x01ffafd4 (ITCM) -- resets the floating-point runtime state that the
// soft-float block above it (0x01ff8000-0x01ffafd0: the double add/multiply, the float
// and double conversions, and the integer division helpers) reads and updates.
//
// It zeroes the status word func_0207322c points at (the word __ieee_status and
// __fp_status rewrite), then the five words at +4..+0x14 of the block func_02073238
// points at; word +0 is left alone. Those five words are the exception handlers
// src/cstd4.cpp's func_0206de14 dispatches through, one per bit of 26-30 in its flags
// argument (0x04000000 -> +4 ... 0x40000000 -> +0x14), so this leaves the status clear
// and no handler installed.
//
// Entry (src/Entry.c), the ARM9 startup code, calls it once: after the DTCM, palette and
// OAM clears, and before the jump to the game. That is the place and job ARM's runtime
// documents for _fp_init ("initialize the floating-point status register before
// performing any floating-point operations"). ARM does not specify _fp_init's body, so
// that name stays a lead.
//
// Assembly in the original, like the whole runtime block it belongs to: it keeps r0 live
// across a `bl` with only `{lr}` pushed, relying on the callee returning its result in r0
// and clobbering nothing else, and it reuses the second callee's return value as the base
// for five stores without ever re-materialising it. mwccarm compiling equivalent C emits a
// callee-saved spill and a real frame; this has neither.

extern void *func_0207322c(void);
extern void *func_02073238(void);

asm void func_01ffafd4(void)
{
    stmdb sp!, {lr}
    bl func_0207322c
    mov r1, #0
    str r1, [r0]
    bl func_02073238
    mov r1, #0
    str r1, [r0, #4]
    str r1, [r0, #8]
    str r1, [r0, #0xc]
    str r1, [r0, #0x10]
    str r1, [r0, #0x14]
    ldmia sp!, {lr}
    bx lr
}
