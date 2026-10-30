extern char data_020a11e4[];
extern void func_02042254(void);
/* local extern: the thread is untyped storage here (void *) */
extern void OS_CreateThread(void *a, void *fn, void *c, void *d, unsigned int e, unsigned int f);
/* local extern: as above */
extern void OS_WakeupThreadDirect(void *a);

void func_02042200(void)
{
    char *base = (char *)(int)data_020a11e4;
    *(short *)(base + 0x494) = 0;
    OS_CreateThread(base + 0x400, (void *)func_02042254, base, base + 0x400, 0x400, 0xf);
    OS_WakeupThreadDirect(base + 0x400);
}
