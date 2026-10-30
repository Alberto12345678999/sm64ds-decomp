/* NitroSDK wm_etc.c WM_MeasureChannel: measure how busy channel is.
 * Refuse unless WM is IDLE (2), register callback for API 0x1e
 * (MEASURE_CHANNEL), write the request into the ARM9-to-ARM7 FIFO buffer
 * (the API id, then ccaMode, edThreshold, channel and measureTime in
 * milliseconds) and send it; WM_ERRCODE_OPERATING (2) once it is queued. */
extern int *WM_GetSystemWork(void);
extern int WM_CheckStateEx(int paramNum, ...);
extern void WM_SetCallbackTable(int i, int val);
extern int WM_SendCommand(short id, unsigned short paramNum, ...);

int WM_MeasureChannel(int callback, int ccaMode, int edThreshold, int channel,
                      unsigned short measureTime) {
    int *sys;
    short *request;
    int result;

    sys = WM_GetSystemWork();
    result = WM_CheckStateEx(1, 2);
    if (result != 0)
        return result;
    WM_SetCallbackTable(0x1e, callback);
    request = (short *)sys[3];
    request[0] = 0x1e;
    request[1] = ccaMode;
    request[2] = edThreshold;
    request[3] = channel;
    request[4] = measureTime;
    result = WM_SendCommand(0x1e, 0);
    if (result != 0)
        return result;
    return 2;
}
