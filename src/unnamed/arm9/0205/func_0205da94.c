#include "nitro/card/card_common.h"

extern unsigned int data_020a805c;

int func_0205da94(int a, int b)
{
    switch (b) {
    case 9:
        CARD_LockRom((unsigned short)data_020a805c);
        return 0;
    case 0xa:
        CARD_UnlockRom((unsigned short)data_020a805c);
        return 0;
    case 1:
        return 4;
    }
    return 8;
}
