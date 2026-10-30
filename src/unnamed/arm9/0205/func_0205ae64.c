/* func_0205ae64 at 0x0205ae64
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (arm9 main).
 */

extern void PXI_SetFifoRecvCallback(int tag, void *callback);
extern int func_020587dc(void);
extern int PXI_IsCallbackReady(int tag, int proc);
extern void OS_SpinWait(unsigned int cycles);
extern void func_0205aed0(void);

void func_0205ae64(void) {
    PXI_SetFifoRecvCallback(7, (void *)func_0205aed0);
    if (func_020587dc()) return;
    if (PXI_IsCallbackReady(7, 1))
        return;
    do {
        OS_SpinWait(0x64);
    } while (!PXI_IsCallbackReady(7, 1));
}
