//cpp
// @symbol _ZN20daObjWanwanShutter_c8BehaviorEv
/* recovered: named members + shared header, real C++ method */
#include "daObjWanwanShutter_c.h"
extern "C" {
extern int _ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(void*, int, int);
}

int daObjWanwanShutter_c::Behavior()
{
    if (*(unsigned char*)((char*)&mDisabled) != 0) return 1;
    _ZN10dBgActor_c13IsClsnInRangeE5Fix12IiES1_(((void *)this), 0, 0);
    return 1;
}
