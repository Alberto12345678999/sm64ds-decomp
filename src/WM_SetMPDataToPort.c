/* NitroSDK wm_mp.c WM_SetMPDataToPort: WM_SetMPDataToPortEx with no callback
 * argument, returning its WM result. pret's SDK makes it an inline; here it
 * is a function. destBitmap stays an int: the u16 that the definition takes
 * adds an instruction here. */
extern int WM_SetMPDataToPortEx(int a0, int z, int a1, int a2, int a3, unsigned short a4,
                                unsigned short a5);

int WM_SetMPDataToPort(int a0, int a1, int a2, int a3, unsigned short a4, unsigned short a5) {
    return WM_SetMPDataToPortEx(a0, 0, a1, a2, a3, a4, a5);
}
