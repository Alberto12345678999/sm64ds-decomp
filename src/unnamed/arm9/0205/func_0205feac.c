#include "nitro/spi/pm.h"

/* PMi_CallCallbackAndUnlock by shape: release the channel, then run and
   clear the pending callback with `a` as its result. */
void func_0205feac(int a) {
    int lock = data_020a8114.lock;
    PMCallback callback = data_020a8114.callback;
    void *arg = data_020a8114.callbackArg;
    if (lock != 0) {
        data_020a8114.lock = 0;
    }
    if (callback == 0) {
        return;
    }
    data_020a8114.callback = 0;
    callback(a, arg);
}
