/* NitroSDK wm_mp.c WM_SetMPDataToPort: WM_SetMPDataToPortEx with no callback
 * argument. pret's SDK makes it an inline; here it is a function. */
extern void WM_SetMPDataToPortEx(int a0, int z, int a1, int a2, int a3, unsigned short a4,
                                 unsigned short a5);

void WM_SetMPDataToPort(int a0, int a1, int a2, int a3, unsigned short a4, unsigned short a5) {
    WM_SetMPDataToPortEx(a0, 0, a1, a2, a3, a4, a5);
}
