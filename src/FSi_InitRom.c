/* NitroSDK FS_rom.c FSi_InitRom, an older revision than pret's (no
 * multiboot-child branch): store the default DMA channel (data_020a8060),
 * take a card lock id, clear the ARM9/ARM7 overlay-table regions, CARD_Init,
 * set up the ROM archive data_020a8074 and register it as "rom", then load
 * it from the ROM header's FNT and FAT regions ({offset, length} at
 * 0x027ffe40 and 0x027ffe48) unless either offset is 0 or ~0. */
#include "types.h"
#include "nitro/os/spinLock.h"

extern u32 data_020a8060;
extern int data_020a805c;
extern int data_020a8064[2];
extern int data_020a806c[2];
extern int data_020a8074;
extern int data_0209a048;
extern int func_0205da94;
extern int func_0205db2c;
extern int func_0205db24;
extern void CARD_Init(void);
extern void func_0205cd34(void *o);
extern int func_0205cc80(void *thiz, void *a, void *b);
extern void func_0205c7c4(int *p, int a, int b);
extern int func_0205cb68(int *self, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

#pragma opt_propagation off
void FSi_InitRom(u32 default_dma_no) {
    int *fnt;
    int *fat;

    data_020a8060 = default_dma_no;
    data_020a805c = OS_GetLockID();
    data_020a8064[0] = 0;
    data_020a8064[1] = 0;
    data_020a806c[0] = 0;
    data_020a806c[1] = 0;
    CARD_Init();

    fnt = (int *)0x27ffe40;
    fat = (int *)0x27ffe48;
    func_0205cd34(&data_020a8074);
    func_0205cc80(&data_020a8074, &data_0209a048, (void *)3);
    if (fnt[0] == -1)
        return;
    if (fnt[0] == 0)
        return;
    if (fat[0] == -1)
        return;
    if (fat[0] == 0)
        return;
    func_0205c7c4(&data_020a8074, (int)&func_0205da94, 0x602);
    func_0205cb68(&data_020a8074, 0, fat[0], fat[1], fnt[0], fnt[1], (int)&func_0205db2c,
                  (int)&func_0205db24);
}
