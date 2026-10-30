extern int func_02062338(void *cb);
extern void func_02040504(void);
extern int data_020a0f94;

/* Disable the wireless hardware: func_02062338 sends WM command 4 (the
   SDK's WM_APIID_DISABLE, stop state only) with func_02040504 as the
   callback. As func_0203fc74 otherwise. */
int func_0203fcec(void) {
    if (func_02062338((void *)func_02040504) != 2) {
        data_020a0f94 = 1;
        return 0;
    }
    return 1;
}
