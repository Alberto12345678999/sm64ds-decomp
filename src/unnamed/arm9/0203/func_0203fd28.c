extern int WM_Enable(void *cb);
extern void func_020405b4(unsigned short *cb);
extern int data_020a0f94;

/* Enable the wireless hardware: WM_Enable sends WM command 3 (the
   SDK's WM_APIID_ENABLE, ready state only) with func_020405b4 as the
   callback. As func_0203fc74 otherwise. */
int func_0203fd28(void) {
    if (WM_Enable((void *)func_020405b4) != 2) {
        data_020a0f94 = 1;
        return 0;
    }
    return 1;
}
