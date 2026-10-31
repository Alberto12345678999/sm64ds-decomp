#ifndef NITRO_SPI_PM_H
#define NITRO_SPI_PM_H

/*
 * The ARM9 side of the NitroSDK power-management PXI channel (spi/ARM9/pm.c),
 * defined in src/engine/spi/PM.cpp. Each function is named by its body
 * against pret's pokediamond and pret's pmd-sky (both carry this file as
 * spi_pm.s); that file's banner gives the evidence. Parameters stay unnamed:
 * a name here takes an @NNN in every C++ includer.
 */

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*PMCallback)(u32 result, void *arg);

/* The channel state at 0x020a8114; its extent is 0x10, the next labelled
   address being data_020a8124. Every sender takes `lock`, stores its
   callback and argument, and sends; PMi_CommonCallback finishes through
   PMi_CallCallbackAndUnlock, which drops `lock` and calls
   callback(result, callbackArg). A command-0x67 reply is stored through
   `replyDst`. The field names describe that use; the SDK's own spellings are
   not recovered. */
struct D020a8114 {
    int lock;
    PMCallback callback;
    void *callbackArg;
    int *replyDst;
};
extern struct D020a8114 data_020a8114;

/* The four register-read slots at 0x020a8138, 8 bytes each: a reply-arrived
   flag and the caller's destination for the reply. PM_Init clears every
   `flag`; PMi_ReadRegisterAsync clears one and stores the caller's buffer in
   `reply`; PMi_CommonCallback stores the halfword reply to commands
   0x70..0x73 through `reply` and sets `flag`.

   `reply` also has its own symbol row, data_020a813c, because both of its
   accesses reach it at that address. As this struct's second field, mwcc
   folds the +4 into the pool literal and names data_020a8138 with a RELA
   addend of 4, which resolves to the same 0x020a813c relocs.txt records. The
   row stays: dsd needs a symbol at every relocs.txt target. Both field names
   are coined. */
typedef struct {
    unsigned short flag;
    unsigned short pad;
    u16 *reply;
} PmEntry;
extern PmEntry data_020a8138[4];

void PM_Init(void);
u32 PM_SendUtilityCommandAsync(u32, PMCallback, void *);
u32 PMi_ReadRegisterAsync(u32, u16 *, PMCallback, void *);
u32 PMi_ReadRegister(u32, u16 *);
u32 PMi_SetLEDAsync(u32, PMCallback, void *);
u32 PMi_SetLED(u32);
u32 PM_SetBackLightAsync(u32, u32, PMCallback, void *);
u32 PM_SetBackLight(u32, u32);
u32 PM_ForceToPowerOffAsync(PMCallback, void *);
u32 PM_ForceToPowerOff(void);
u32 PM_GetBackLight(int *, int *);
void PM_GoSleepMode(u32, u32, u32);
int PMi_SetLCDPower(u32, u32, int, int);
int PM_SetLCDPower(u32);
int PM_GetLCDPower(void);
u32 PMi_SendLEDPatternCommandAsync(u32, PMCallback, void *);
u32 PMi_SendLEDPatternCommand(u32);

#ifdef __cplusplus
}
#endif

#endif
