/* The backup identify task func_020603c8 runs: put the first word of the
 * device entry func_02060364 selected (func_02060470) in the request's type
 * field, send CARD_REQ_IDENTIFY, then end the task. */
#include "nitro/card/card_common.h"

extern int func_02060470(void);

void func_020607e8(CARDiCommon *p) {
    p->cmd->type = func_02060470();
    CARDi_Request(p, CARD_REQ_IDENTIFY, 1);
    CARDi_EndTask(p);
}
