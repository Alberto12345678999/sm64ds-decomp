/* NitroSDK wm_ds.c WM_GetSharedDataAddress: where member aid's data sits
 * in a received data-sharing set, or 0 for a null dsInfo or receiveData
 * or when the set holds nothing from aid (its receivedBitmap bit is
 * clear). func_02062734 does the lookup through the set's aidHeader. */
#include "types.h"

/* NitroSDK WMDataSet, as WM_StepDataSharing spells it. */
typedef struct WMDataSet {
    u16 aidHeader;      /* 0x00 -- members whose data the set holds */
    u16 receivedBitmap; /* 0x02 */
    u16 data[0x7e];     /* 0x04 */
} WMDataSet;

extern unsigned func_02062734(char *dsInfo, unsigned aidHeader, unsigned data, int aid);

unsigned WM_GetSharedDataAddress(char *dsInfo, WMDataSet *receiveData, int aid) {
    if (dsInfo == 0)
        return 0;
    if (receiveData == 0)
        return 0;
    if ((receiveData->receivedBitmap & (1u << aid)) == 0)
        return 0;
    return func_02062734(dsInfo, receiveData->aidHeader, (unsigned)receiveData->data, aid);
}
