extern int func_020620b0(void *f, int x);
extern void func_020401e8(unsigned short *cb);
extern int data_020a0f44;
/* Set the parent parameters: WM_SetParentParameter (func_020620b0) on the
   WMParentParam in data_020a0f44, with func_020401e8 as the callback, which
   starts the parent (func_0203fb98). 1 when the request is accepted (2). */
int func_0203fbc4(void) {
    return func_020620b0((void *)func_020401e8, data_020a0f44) == 2;
}
