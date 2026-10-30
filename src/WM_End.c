/* NitroSDK wm_standard.c WM_End: IDLE back to READY in one step (power off,
 * then give up the hardware). Refuse unless WM is in state IDLE (2), register
 * callback for API 2 (END) and send that command with no parameters;
 * WM_ERRCODE_OPERATING (2) once it is queued, the callback reporting the
 * result. */
extern int WM_CheckStateEx(int paramNum, ...);
extern void WM_SetCallbackTable(int i, int val);
extern int WM_SendCommand(short id, unsigned short paramNum, ...);

int WM_End(int callback) {
    int result;

    result = WM_CheckStateEx(1, 2);
    if (result != 0)
        return result;
    WM_SetCallbackTable(2, callback);
    result = WM_SendCommand(2, 0);
    if (result != 0)
        return result;
    return 2;
}
