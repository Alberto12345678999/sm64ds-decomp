//cpp
// @symbol _ZN6Player19func_ov002_020d71a0Ev
#include "Player.h"
extern "C" {
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void *anim, void *file, int a, int b, unsigned short u);
struct G { int w[2]; };
extern struct G data_ov002_0210eb88;
}

void Player::func_ov002_020d71a0() {
    char *p = (char*)this;
    *(unsigned char *)(p + 0x714) = 0;
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(*(char **)(p + 0x160), (void *)data_ov002_0210eb88.w[1], 0x40000000, 0x1000, 0);
    *(int *)(*(char **)(p + 0x160) + 0x58) = 0;
}
