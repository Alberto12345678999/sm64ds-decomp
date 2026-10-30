#include "Ov007Work.h"

extern void func_ov007_020c421c(char *x);

void func_ov007_020b2728(void) {
    int i;
    for (i = 0; i < 3; i++) {
        func_ov007_020c421c((char *)WORK->screenSprites[i]);
    }
}
