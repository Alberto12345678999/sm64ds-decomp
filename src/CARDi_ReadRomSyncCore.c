/* NitroSDK CARDi_ReadRomSyncCore (card_rom.c): the read task. CARDi_ReadRom
 * hands it to CARDi_SetTask for an asynchronous read and calls it directly
 * for a synchronous one. The argument is the CARDiCommon block, unused.
 */
#include "nitro/card/card_rom.h"

extern int CARDi_ReadFromCache(CARDRomStat *p);
extern void CARDi_ReadEnd(void);

void CARDi_ReadRomSyncCore(CARDiCommon *c) {
    CARDRomStat *const p = &rom_stat;
    if (CARDi_ReadFromCache(p)) {
        p->read_func(p);
    }
    CARDi_ReadEnd();
}
