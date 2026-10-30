/* NitroSDK CARDi_ReadRomSyncCore (card_rom.c): the read task. CARDi_ReadRom
 * hands it to CARDi_SetTask for an asynchronous read and calls it directly
 * for a synchronous one. The argument is the CARDiCommon block, unused.
 */
#include "types.h"
#include "nitro/card/card_common.h"

extern int func_02060ebc(void *stat); /* CARDi_ReadFromCache */
extern void func_02060e38(void);      /* end the read */

/* NitroSDK CARDRomStat (rom_stat), the field read here: the routine that
 * reads what the cache does not hold (CARD_Init installs it). */
typedef struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *);
} CARDRomStat;

extern CARDRomStat data_020a8780; /* rom_stat */

void CARDi_ReadRomSyncCore(CARDiCommon *c) {
    CARDRomStat *const p = &data_020a8780;
    if (func_02060ebc(p)) {
        p->read_func(p);
    }
    func_02060e38();
}
