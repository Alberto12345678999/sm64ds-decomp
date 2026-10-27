//cpp
#include "Player.h"

extern "C" {

extern int func_0200e6d8(int);
extern int func_0200e5fc(int);
int func_0200e5ac(void *c, void *r1, void *r2) {
    int r = func_0200e6d8(*(unsigned char *)((char *)c + 1));
    if (r == 0) {
        r = func_0200e5fc(*(unsigned char *)((char *)c + 1));
        if (r == 0)
            return 0;
    }
    /* The Kuppa-script player command dispatcher in ov002's Player TU. */
    return ((Player *)r)->func_ov002_020bd664((unsigned char *)c, (int)r1, (int)r2);
}
}
