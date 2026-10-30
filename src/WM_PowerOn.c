/* NitroSDK wm_standard.c WM_PowerOn: STOP to IDLE, powering the wireless
 * hardware on. Refuse unless WM is in state STOP (1), register callback for API
 * 5 (POWER_ON) and send that command with no parameters; WM_ERRCODE_OPERATING
 * (2) once it is queued, the callback reporting the result. */
extern int WM_CheckStateEx(int paramNum, ...);
extern void WM_SetCallbackTable(int i, int val);
extern int WM_SendCommand(short id, unsigned short paramNum, ...);

int WM_PowerOn(int callback) {
    int result;

    result = WM_CheckStateEx(1, 1);
    if (result != 0)
        return result;
    WM_SetCallbackTable(5, callback);
    result = WM_SendCommand(5, 0);
    if (result != 0)
        return result;
    return 2;
}
