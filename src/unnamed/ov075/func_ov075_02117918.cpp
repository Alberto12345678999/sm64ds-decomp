//cpp
#include "PlayerInput.h"
#include "G2x.h"
#include "dScEntry_c.h"

extern "C" {

typedef short s16;

extern void func_ov075_02115e8c(char *self, int a, int b, s16 c, s16 e);
extern int func_0200f0bc(void);
extern int LoadFile(int handle);
extern void func_ov075_02116030(void *c, int v);
extern void SetBg2Offset(int a, int b);
extern void func_02033bb8(int a);
extern void func_02020304(void);

extern unsigned char data_0209f4ae[];
extern s16 data_ov075_0211b5d4[];
extern unsigned char data_0209d454[];
extern int data_ov075_0211c9b8[];
extern int data_ov075_0211d71c[];
extern unsigned char data_0209d45c[];

void func_ov075_02117918(char *self)
{
    dScEntry_c *scene = (dScEntry_c *)self;
    int i;
    int r;
    int v;
    char *p;

    i = 0;
    p = (char *)scene->mIcons;
    v = 0x30;
    scene->mSelectedIcon = data_0209f4ae[gActivePlayerSlot * 0x18];

    for (; i <= 2; i++) {
        func_ov075_02115e8c(p, 0, 0, 0x80, (s16)v);
        v += 0x28;
        p += 0x24;
    }

    scene->mIcons[scene->mSelectedIcon].mOn = 1;

    func_ov075_02115e8c((char *)&scene->mIcons[3], 0xb, 0, 0x80, 0xa8);

    r = func_0200f0bc();
    func_ov075_02115e8c((char *)&scene->mIcons[4], 0xc, 0, data_ov075_0211b5d4[r], 0xa8);

    scene->mIconCount = 5;
    data_0209d454[0] &= ~5;

    r = func_0200f0bc();
    func_ov075_02116030(data_ov075_0211d71c, LoadFile(data_ov075_0211c9b8[r]));

    if (scene->mSelectedIcon == 0)
        SetBg2Offset(0, 0);
    else if (scene->mSelectedIcon == 1)
        SetBg2Offset(0x100, 0);
    else
        SetBg2Offset(0, 0x100);

    func_02033bb8(5);
    data_0209d45c[0] |= 4;
    data_0209d454[0] |= 5;
    G2x::SetBlendBrightness((volatile unsigned short *)0x4000050, 0xb, ~5);

    scene->mStepWork[0] = scene->mSelectedIcon;
    func_02020304();
}
}
