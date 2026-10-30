/* NitroSDK CARDi_ReadRomSyncCore (card_rom.c): the read task. CARDi_ReadRom
 * hands it to CARDi_SetTask for an asynchronous read and calls it directly
 * for a synchronous one. The argument is the CARDiCommon block, unused.
 */
#include "types.h"
#include "nitro/card/card_common.h"

extern int CARDi_ReadFromCache(void *stat); /* CARDi_ReadFromCache */
extern void CARDi_ReadEnd(void);      /* end the read */

/* NitroSDK CARDRomStat (rom_stat), the field read here: the routine that
 * reads what the cache does not hold (CARD_Init installs it). */
typedef struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *);
} CARDRomStat;

extern CARDRomStat rom_stat; /* rom_stat */

void CARDi_ReadRomSyncCore(CARDiCommon *c) {
    CARDRomStat *const p = &rom_stat;
    if (CARDi_ReadFromCache(p)) {
        p->read_func(p);
    }
    CARDi_ReadEnd();
}
