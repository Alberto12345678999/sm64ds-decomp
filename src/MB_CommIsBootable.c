#include "types.h"
#include "private/arm9_a9db8_mb_parent.h"

#define MB_COMM_PSTATE_SEND_COMPLETE 7

/* The SDK's pPwork; char * is the spelling the other MB parent files share. */
extern char *data_020a9db8;
#define MB_WORK ((MbParentWork *)data_020a9db8)

extern int func_02065edc(unsigned int x); /* aid in 1..15 */

/* NitroSDK mb_parent.c: the child at aid can be booted once it has the
 * whole download. */
int MB_CommIsBootable(u16 aid) {
    if (data_020a9db8 != 0 && func_02065edc(aid) &&
        MB_WORK->mChildState[aid - 1] == MB_COMM_PSTATE_SEND_COMPLETE)
        return 1;
    return 0;
}
