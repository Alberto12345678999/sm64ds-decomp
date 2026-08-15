#include "types.h"
extern void *_ZN9ActorBasenwEj(unsigned);
extern void _ZN9ActorBaseC1Ev(void *);

extern int data_0208e4b8[];
extern int _ZTV5Scene[];
extern int _ZTV7dScMB_c[];
extern int _ZTV8dFader_c[];
extern int _ZTV15dFdBrightness_c[];
extern int _ZTV10dFdColor_c[];
void *func_020352b4(void)
{
    char *p = (char *)_ZN9ActorBasenwEj(0x68);
    if (p) {
        _ZN9ActorBaseC1Ev(p);
        *(int **)p = data_0208e4b8;
        *(int **)p = _ZTV5Scene;
        {
            u8 *bp = (u8 *)((int)p + 0x13);
            *bp |= 1;
            *bp |= 4;
        }
        *(int **)p = _ZTV7dScMB_c;
        {
            int *fp = (int *)((int)p + 0x50);
            fp[0] = (int)_ZTV8dFader_c;
            fp[0] = (int)_ZTV15dFdBrightness_c;
            fp[1] = 0x1000;
            fp[2] = 0;
            fp[0] = (int)_ZTV10dFdColor_c;
            *(short *)(fp + 3) = 0;
        }
    }
    return p;
}
