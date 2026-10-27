//cpp
#include "dCamera_c.h"

extern "C" {

extern int func_02009d30(int arg);

int func_02009a8c(int arg) {
    ((dCamera_c *)arg)->SaveCameraStateBeforeTalk();
    return func_02009d30(arg);
}
}
