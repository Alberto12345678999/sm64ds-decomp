// HAND-ASM PRIMITIVE: byte-faithful asm-block match. This function was assembly
// in the original (SDK/runtime primitive: block copy, matrix/math, CP15, context
// switch, etc.), so there is no C to decompile it to -- the asm block is the
// faithful source. Counts as matched (asm-primitive policy), not a C transcription.
// MTX_RotX33_ @ 0x02052550 (arm9, Thumb): the Nitro SDK's FX_mtx33.c X rotation,
// {1, 0, 0, 0, c, s, 0, -s, c} from (sin, cos) with 4096 = 1.0, as
// pret/pokediamond's asm body has it.
#pragma thumb on
asm void MTX_RotX33_(int *m, int s, int c) {
    mov r3, #1
    lsl r3, r3, #12
    str r3, [r0, #0]
    mov r3, #0
    str r3, [r0, #4]
    str r3, [r0, #8]
    str r3, [r0, #12]
    str r2, [r0, #16]
    str r1, [r0, #20]
    str r3, [r0, #24]
    neg r1, r1
    str r1, [r0, #28]
    str r2, [r0, #32]
    bx lr
}
