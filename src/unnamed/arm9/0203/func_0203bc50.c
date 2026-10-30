/* Clear the four per-player key records (data_020a0e58, held and pressed,
   as func_0203bc7c fills them). The soft reset (func_02023498 in
   func_0202345c.cpp) runs it every frame while a reset is pending. */
extern short data_020a0e58[];

void func_0203bc50(void)
{
    short *p = data_020a0e58;
    int i;
    for (i = 0; i < 4; i++) {
        p[0] = 0;
        p[1] = 0;
        p += 2;
    }
}
