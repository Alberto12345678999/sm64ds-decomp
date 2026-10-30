#ifndef NITRO_SPI_PM_H
#define NITRO_SPI_PM_H

/*
 * The ARM9 side of the NitroSDK power-management PXI channel (spi/ARM9/pm.c).
 * The functions keep their address names; each is matched to an SDK function
 * by its body against pret/pmd-sky's lib/NitroSDK/asm/spi_pm.s:
 *   func_0205ff20  PMi_Lock                   test-and-set of `lock`
 *   func_0205ff08  PMi_WaitBusy               spins until `lock` clears
 *   func_0205feac  PMi_CallCallbackAndUnlock  clears `lock`, runs `callback`
 *   func_0205fcfc  PMi_CommonCallback         the tag-8 PXI receive callback
 *   func_0205fbd0  PM_SendUtilityCommandAsync command 0x63
 *   func_0205fb58  PMi_ReadRegisterAsync      command 0x65
 * func_0205f5fc sends command 0x66 the same way; pmd-sky's newer SDK has no
 * 0x66 sender to compare it with.
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

/* The four register-read slots at 0x020a8138, 8 bytes each. PM_Init clears
   every `flag`, PMi_ReadRegisterAsync clears one and stores its buffer in
   `arg`, and PMi_CommonCallback sets it when commands 0x70..0x73 answer. The
   word at +4 carries its own label, data_020a813c, which PMi_CommonCallback
   reads as the short * it stores the reply through, so the two symbols are
   one array seen twice. */
typedef struct {
    unsigned short flag;
    unsigned short pad;
    int arg;
} PmEntry;
extern PmEntry data_020a8138[4];

#ifdef __cplusplus
}
#endif

#endif
