//cpp
#include "G2x.h"
#include "dScEntry_c.h"

extern "C" {

extern unsigned char data_0209d45c;
extern unsigned char data_0209d454;
extern int data_ov075_0211d71c[];
extern void func_ov075_02116028(int *p, int v);
extern void func_020338b0(int a, int b, int c, int d);
/* A dScEntry_c::Step: the step-set data at 0x0211c8a0 points at it. */

void func_ov075_02117ac4(char *r4) {
    data_0209d45c = data_0209d45c & (~0xe);
    data_0209d454 = data_0209d454 & (~1);
    func_ov075_02116028(data_ov075_0211d71c, 6);
    func_020338b0(0x145, 0xb0, 0x17, -1);
    data_0209d454 = data_0209d454 | 5;
    ((dScEntry_c *)r4)->mIconCount = 0;
    G2x::SetBlendBrightness((volatile unsigned short *)0x4000050, 0x1f, ~5);
    ((dScEntry_c *)r4)->mStepDelay = 2;
}
}
