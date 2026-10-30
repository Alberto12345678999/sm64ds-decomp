typedef void (*fn_t)(void);

/* Run the static-initializer table at 0x02086b60 (the __sinit_* pointers)
   in order until its null entry. The entry code (Entry.c) calls it last,
   just before it jumps to 0x02007000. */
void func_02072f94(void) {
    fn_t *p = (fn_t *)0x2086b60;
    fn_t f;
    while (p != 0 && (f = *p) != 0) {
        f();
        p++;
    }
}
