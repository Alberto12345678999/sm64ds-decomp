// NONMATCHING (NOT-C-EXPRESSIBLE): byte-exact hand-written asm. A bare epilogue / mid-frame
// exit stub the symbol table split out, not a real function - no standalone C construct
// produces it. Nothing here to match - see notes/arm9-endgame.md.
extern void func_020731fc(void);
extern void __end__catch(void);
extern void __rethrow(void);

asm void func_0207335c(void) {
    str sp, [r11, #0x2c]
    subs r7, r7, #1
    beq done
loop:
    sub r4, r4, r6
    mov r0, r4
    blx r5
    subs r7, r7, #1
    bne loop
    b done
    bl func_020731fc
    add r0, r11, #0x18
    bl __end__catch
    ldr sp, [r11, #0x2c]
done:
    bl __rethrow
    add r0, r11, #0
    bl __end__catch
    add sp, r11, #0x30
    ldmia sp!, {r4, r5, r6, r7, r11, lr}
    bx lr
}
