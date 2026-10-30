extern int func_02061e38(void *cb, int arg, int z);
extern void func_0203fec4(void);
extern int data_020a0f54;

/* Connect to the chosen parent: WM_StartConnect (func_02061e38) on the
   WMBssDesc in data_020a0f54, no SSID, with func_0203fec4 as the callback.
   1 when the request is accepted (2). */
int func_0203fb5c(void) {
    return func_02061e38((void *)func_0203fec4, data_020a0f54, 0) == 2;
}
