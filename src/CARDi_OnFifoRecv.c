/* NitroSDK CARDi_OnFifoRecv (card_request.c): the PXI callback for the FS
 * tag (0xb), which CARDi_InitCommon registers. ARM7's reply ends the request
 * in flight, so clear CARD_STAT_REQ and wake the thread that sent it.
 */
#include "types.h"
#include "nitro/card/card_common.h"

#define PXI_FIFO_TAG_FS 0xb

extern void OS_WakeupThreadDirect(void *thread);

void CARDi_OnFifoRecv(int tag, u32 data, int err)
{
    if (tag == PXI_FIFO_TAG_FS && err) {
        CARDiCommon *const p = &cardi_common;
        p->flag &= ~CARD_STAT_REQ;
        OS_WakeupThreadDirect(p->cur_th);
    }
}
