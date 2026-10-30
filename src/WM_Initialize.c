/* NitroSDK wm_standard.c WM_Initialize: READY to IDLE in one step. Run
 * WM_Init on wmSysBuf with DMA channel dmaNo, register callback for API 0
 * (INITIALIZE) and send that command with the three buffers WM_Enable
 * sends; ARM7 then enables and powers on the hardware itself.
 * WM_ERRCODE_OPERATING (2) once it is queued. */
extern int WM_Init(int a, int b);
extern void WM_SetCallbackTable(int i, int val);
extern int *WM_GetSystemWork(void);
extern int WM_SendCommand(short id, unsigned short paramNum, ...);

int WM_Initialize(int wmSysBuf, int callback, int dmaNo) {
    int *sys;
    int result;

    result = WM_Init(wmSysBuf, dmaNo);
    if (result != 0)
        return result;
    WM_SetCallbackTable(0, callback);
    sys = WM_GetSystemWork();
    result = WM_SendCommand(0, 3, sys[0], sys[1], sys[4]);
    if (result != 0)
        return result;
    return 2;
}
