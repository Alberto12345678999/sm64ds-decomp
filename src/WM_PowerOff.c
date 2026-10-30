/* NitroSDK wm_standard.c WM_PowerOff: IDLE back to STOP, powering the wireless hardware off. Refuse unless WM is
 * in state IDLE (2), register callback for API 6 (POWER_OFF) and send
 * that command with no parameters; WM_ERRCODE_OPERATING (2) once it is
 * queued, the callback reporting the result. */
extern int WM_CheckStateEx(int paramNum, ...);
extern void WM_SetCallbackTable(int i, int val);
extern int WM_SendCommand(short id, unsigned short paramNum, ...);

int WM_PowerOff(int callback) {
    int result;

    result = WM_CheckStateEx(1, 2);
    if (result != 0)
        return result;
    WM_SetCallbackTable(6, callback);
    result = WM_SendCommand(6, 0);
    if (result != 0)
        return result;
    return 2;
}
