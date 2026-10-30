extern int data_020737a8;
/* __sinit_d_camera.cpp, the first contribution in arm9 .init. The C lexer
   cannot spell that dotted linker name; ARM9_INIT_START is that base. */
extern void ARM9_INIT_START(void);
int func_02071844(void **p)
{
    p[3] = &data_020737a8;
    p[4] = (void *)ARM9_INIT_START;
    return 1;
}
