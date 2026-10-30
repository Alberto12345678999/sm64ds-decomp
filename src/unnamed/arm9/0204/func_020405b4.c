#include "types.h"
extern int func_0203fcec(void);
extern int func_0203fcb0(void);
extern int data_020a0f5c;
extern int data_020a0f94;

/* The callback func_0203fd28 hands the enable request; p[1] is the
   errcode. On success, for target mode data_020a0f5c 0 disable the
   hardware again (func_0203fcec); for 3 or 4 power it on (func_0203fcb0).
   An error sets the link status data_020a0f94 to 1. */
void func_020405b4(u16 *p)
{
    if (p[1] == 0) {
        switch (data_020a0f5c) {
        case 0:
            func_0203fcec();
            return;
        case 3:
        case 4:
            func_0203fcb0();
            return;
        }
        return;
    }
    data_020a0f94 = 1;
}
