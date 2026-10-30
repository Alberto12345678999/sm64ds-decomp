extern char data_020a11e4[];
extern void func_02042254(void);
/* local extern: the thread is untyped storage here (void *) */
extern void OS_CreateThread(void *a, void *fn, void *c, void *d, unsigned int e, unsigned int f);
/* local extern: as above */
extern void OS_WakeupThreadDirect(void *a);

/* Start the file-share parent's loader thread (func_02042254).
   data_020a11e4 is its 0x400-byte stack, and the OSThread follows at +0x400
   (also the symbol data_020a15e4, which func_020423c8 wakes).
   OS_CreateThread takes (thread, entry, arg, stack top, stack size,
   priority 15 here), and OS_WakeupThreadDirect then wakes the thread.
   The halfword at +0x494 is the OSThread's +0x94, a field of the thread
   cleared here before OS_CreateThread runs. The (int) launder keeps the one
   base register the ROM uses for every address. */
void func_02042200(void)
{
    char *base = (char *)(int)data_020a11e4;
    *(short *)(base + 0x494) = 0;
    OS_CreateThread(base + 0x400, (void *)func_02042254, base, base + 0x400, 0x400, 0xf);
    OS_WakeupThreadDirect(base + 0x400);
}
