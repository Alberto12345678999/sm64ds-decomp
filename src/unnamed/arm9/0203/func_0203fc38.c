extern int func_02061ce4(void *cb);
extern void func_02040384(void);
extern int data_020a0f94;

/* Install func_02040384 as the WM indication callback: func_02061ce4 stores
   it in the WM system work under the IRQ lock and returns 0, the SDK's
   WM_SetIndCallback. A refusal sets the link status data_020a0f94 to 1
   (error). */
int func_0203fc38(void) {
    if (func_02061ce4((void *)func_02040384) != 0) {
        data_020a0f94 = 1;
        return 0;
    }
    return 1;
}
