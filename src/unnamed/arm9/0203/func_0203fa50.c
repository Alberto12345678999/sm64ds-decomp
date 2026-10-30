extern unsigned short data_020a0f14;
extern void *data_020a0f74;
extern int func_020631dc(void *a, int b, int c, int d, int e);

/* Start data sharing once MP is running: func_020631dc is WM_StartDataSharing
   (its banner) on the 0x420-byte WMDataSharingInfo func_020408b0 allocates
   into data_020a0f74, port 0xc, the four AIDs 0..3 (0xf), 0x20 bytes per
   station, and double mode when data_020a0f14 (func_020408b0's argument) is
   at most 1. 1 when it succeeds, 0 when it fails. */
int func_0203fa50(void) {
    int flag = (data_020a0f14 <= 1) ? 1 : 0;
    int r = func_020631dc(data_020a0f74, 0xc, 0xf, 0x20, flag);
    if (r)
        return 0;
    return 1;
}
