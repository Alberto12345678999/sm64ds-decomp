extern void *_ZTVN5dPa_c7level_c10callback_cE;
extern void *_ZTVN5dPa_c7level_c16simpleCallback_cE;
void func_020226a4(char *p)
{
    *(void **)p = &_ZTVN5dPa_c7level_c10callback_cE;
    *(void **)p = &_ZTVN5dPa_c7level_c16simpleCallback_cE;
    *(short *)(p + 4) = 0;
}
