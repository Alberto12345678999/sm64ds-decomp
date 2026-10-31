typedef void (*fn_t)(void);

/* The Metrowerks runtime's __call_static_initializers: run the
   static-initializer table at 0x02086b60 (the __sinit_* pointers) in order
   until its null entry. _start calls it last, just before it jumps to
   NitroMain, where pret's NitroSDK crt0 calls it by name. */
void __call_static_initializers(void) {
    fn_t *p = (fn_t *)0x2086b60;
    fn_t f;
    while (p != 0 && (f = *p) != 0) {
        f();
        p++;
    }
}
