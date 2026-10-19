#ifndef CAPICONMGR_H
#define CAPICONMGR_H

#include "CapIcon.h"

// Reconstructed names for the shared cap-icon manager/list state.
extern "C" {
extern u8 gCapIconFlashTimer;
extern u8 gCapIconDispatchLocked;
// Observed character indices are 0..2. Three entries plus natural alignment
// and an original four-entry declaration cannot be distinguished in the ROM.
extern u8 gCapIconRequestFlags[3];
extern u8 gCapIconDispatchFlags[3];
// Unlink also reads index 3 after setting mCharacter to its sentinel value.
extern u8 gCapIconCounts[4];
extern dCapIcon_c *gCapIconListHeads[3];
}

#endif
