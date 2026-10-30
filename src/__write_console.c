void func_02071974(int arg);

/* MSL __write_console for the debug console: send *pcount bytes from base
   one at a time through func_02071974, the ARM semihosting SYS_WRITEC call
   (swi 0x123456, r0 = 3). Returns 0. */
int __write_console(int a, int base, int *pcount) {
    int count = *pcount;
    int i;
    for (i = 0; (unsigned)i < (unsigned)count; i++) {
        func_02071974(base + i);
    }
    return 0;
}
