#include "types.h"
#include "WmWork.h"
extern char *data_020a9db4;

struct Pair { s16 a; s16 b; };

/* Report a failed WM call. x is the API id and kind the WM error code. The
   call is dropped if it succeeded (0) or is still running (2, OPERATING).
   Otherwise {id, code} goes to WmWork.userCallback as event 0xff,
   func_02066a94's failed-WM-call code. */
void func_0206879c(int x, int kind)
{
    struct Pair p;
    if (kind == 2)
        return;
    if (kind == 0)
        return;
    p.a = (s16)x;
    p.b = (s16)kind;
    WM_WORK->userCallback(0xff, &p);
}
