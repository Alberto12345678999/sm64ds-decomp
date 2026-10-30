//cpp
/* The backup write task func_02060484 runs (the send-and-verify mode of
 * pret's CARDi_RequestStreamCommandCore): copy up to a page of the source
 * into backup_cache_page_buf, flush it, program it (CARD_REQ_PROGRAM_BACKUP,
 * 10 retries) and verify it, and advance until len is 0 or a request fails;
 * then end the task. */
#include "types.h"
#include "CP15.h"
#include "nitro/card/card_common.h"

extern "C" {

/* MI_CpuCopy8. Addresses as ints: the void * spelling the other callers use
 * swaps buf and len between r8 and r9 here. */
extern void CpuCopy8(int src, int dst, unsigned int len);

void func_0206062c(CARDiCommon *p) {
    u8 *buf = p->backup_cache_page_buf;
    do {
        u32 len = p->len;
        u32 src = p->src;
        if (len > sizeof(p->backup_cache_page_buf))
            len = sizeof(p->backup_cache_page_buf);
        CpuCopy8(src, (int)buf, len);
        CP15::FlushAndInvalidateDataCache((u32)buf, len);
        CP15::DrainWriteBuffer();
        p->cmd->src = (u32)buf;
        p->cmd->dest = p->dst;
        p->cmd->len = len;
        if (!CARDi_Request(p, CARD_REQ_PROGRAM_BACKUP, 10))
            break;
        if (!CARDi_Request(p, CARD_REQ_VERIFY_BACKUP, 1))
            break;
        p->src += len;
        p->dst += len;
        p->len -= len;
    } while (p->len != 0);
    CARDi_EndTask(p);
}
}
