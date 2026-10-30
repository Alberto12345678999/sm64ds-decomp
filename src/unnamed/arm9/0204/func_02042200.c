extern char data_020a11e4[];
extern void func_02042254(void);
extern void func_02058200(void *a, void *fn, void *c, void *d, int e, int f);
extern void func_02058048(void *a);

/* Start the file-share parent's loader thread (func_02042254).
   data_020a11e4 is its 0x400-byte stack, and the OSThread follows at +0x400
   (also the symbol data_020a15e4, which func_020423c8 wakes).
   func_02058200 has OS_CreateThread's arguments (thread, entry, arg, stack
   top, stack size, priority 15), and func_02058048 then wakes the thread. The
   halfword at +0x494 has no known reader. The (int) launder keeps the one
   base register the ROM uses for every address. */
void func_02042200(void)
{
    char *base = (char *)(int)data_020a11e4;
    *(short *)(base + 0x494) = 0;
    func_02058200(base + 0x400, (void *)func_02042254, base, base + 0x400, 0x400, 0xf);
    func_02058048(base + 0x400);
}
