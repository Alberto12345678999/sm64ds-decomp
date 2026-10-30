// HAND-ASM PRIMITIVE: byte-faithful asm-block match. This function was assembly
// in the original (SDK/runtime primitive: block copy, matrix/math, CP15, context
// switch, etc.), so there is no C to decompile it to -- the asm block is the
// faithful source. Counts as matched (asm-primitive policy), not a C transcription.
// MTX_Rot22_ @ 0x020524e4 (arm9, Thumb): the Nitro SDK's FX_mtx22.c rotation,
// {cos, sin, -sin, cos} from (sin, cos), as pret/pokediamond's asm body has it.
#pragma thumb on
asm void MTX_Rot22_(int *m, int s, int c) {
    str r2, [r0, #0]
    str r1, [r0, #4]
    neg r1, r1
    str r1, [r0, #8]
    str r2, [r0, #12]
    bx lr
}
