#include "types.h"

/* The fields of mb_gameinfo.c's MbBeaconSendStatus (data_020a9d2c) that
   this function writes. */
struct MbBeaconSendStatus {
    void *gameInfoListTop; /* 0x0 */
    void *nowGameInfop;    /* 0x4 */
    u8 *srcp;              /* 0x8 */
    u8 state;              /* 0xc */
};
extern struct MbBeaconSendStatus data_020a9d2c;
extern void MBi_ClearSendStatus(void);

/* NitroSDK MB_InitSendGameInfoStatus (mb_gameinfo.c): reset the beacon send
   status. It empties the game record list, clears the current record, sets
   state 1 (pick a record) and clears the send counters. The parent setup
   func_02068ae8 calls it after it clears the file table.

   Later SDKs have one more statement, `sSendVolatCallback = NULL;`. It
   clears the hook that MB_SetSendVolatCallback installs. This SDK has no
   such hook: its MBi_SendVolatBeacon (func_02067f68) calls no callback, so
   there is nothing to clear. That is the same kind of older-SDK difference
   as MB_SendGameInfoBeacon taking no ggid/tgid/attr. */
void MB_InitSendGameInfoStatus(void) {
    data_020a9d2c.gameInfoListTop = 0;
    data_020a9d2c.nowGameInfop = 0;
    data_020a9d2c.state = 1;
    MBi_ClearSendStatus();
}
