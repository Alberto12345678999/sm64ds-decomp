/* NitroSDK wm_standard.c WM_Enable: READY to STOP, claiming the wireless
 * hardware. Refuse unless WM is in state READY (0), register callback for
 * API 3 (ENABLE) and send that command with the three buffers ARM7 works
 * in: its own work area, the shared status and the ARM7-to-ARM9 FIFO
 * (WM_Init carved all three out of the system buffer).
 * WM_ERRCODE_OPERATING (2) once it is queued. */
extern int WM_CheckStateEx(int paramNum, ...);
extern void WM_SetCallbackTable(int i, int val);
extern int *WM_GetSystemWork(void);
extern int WM_SendCommand(short id, unsigned short paramNum, ...);

int WM_Enable(int callback) {
    int result;
    int *sys;

    result = WM_CheckStateEx(1, 0);
    if (result != 0)
        return result;
    WM_SetCallbackTable(3, callback);
    sys = WM_GetSystemWork();
    result = WM_SendCommand(3, 3, sys[0], sys[1], sys[4]);
    if (result != 0)
        return result;
    return 2;
}
