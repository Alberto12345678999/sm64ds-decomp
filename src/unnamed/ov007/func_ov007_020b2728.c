#include "Ov007Work.h"
#include "Ov007Sprite.h"

void func_ov007_020b2728(void) {
    int i;
    for (i = 0; i < 3; i++) {
        func_ov007_020c421c(WORK->screenSprites[i]);
    }
}
