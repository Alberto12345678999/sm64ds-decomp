#include "types.h"

/* NitroSDK SND_main.c SND_Init, as in pret's pokediamond, once only. This
 * older SDK has no sound mutex, so SND_Init is the file's one function. */
extern s32 data_020a6480; /* sSndInitialized */

extern void SND_CommandInit(void);
extern void SND_AlarmInit(void);

void SND_Init(void) {
    if (data_020a6480)
        return;
    data_020a6480 = 1;
    SND_CommandInit();
    SND_AlarmInit();
}
