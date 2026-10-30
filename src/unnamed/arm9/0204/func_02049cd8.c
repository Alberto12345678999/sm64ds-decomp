extern void MultiStore16(unsigned short val, char *dst, int nbytes);
extern void func_0205a8c4(void *c);
extern int func_020507e0(void *a, void *b, int c, int d, int e, void *f, void *g);
extern char data_020a4c70[];
extern int data_020a4c64;
extern void func_02049ba8(void);

/* Start the sound-capture effect: clear its state (0xc0 bytes at
   data_020a4c70), set the effect kind data_020a4c64 to mode, and for kind
   1 call func_0205a8c4(0x3000) as func_02049c48 does. Then start the
   capture (func_020507e0) on buffer a of size b at 32000 Hz, interval 2,
   with func_02049ba8 as the callback and data_020a4c64 as its context.
   Sound.cpp's sound setup (func_020133bc) starts it with 0x1000 bytes and
   kind 0. */
void func_02049cd8(void *a, void *b, int mode)
{
    volatile unsigned short tmp = 0;
    MultiStore16(tmp, data_020a4c70, 0xc0);
    data_020a4c64 = mode;
    if (mode == 1)
        func_0205a8c4((void *)0x3000);
    func_020507e0(a, b, 0, 0x7d00, 2, (void *)func_02049ba8, &data_020a4c64);
}
