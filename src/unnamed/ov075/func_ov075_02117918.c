#include "PlayerInput.h"
typedef short s16;

extern void func_ov075_02115e8c(char *self, int a, int b, s16 c, s16 e);
extern int func_0200f0bc(void);
extern int LoadFile(int handle);
extern void func_ov075_02116030(void *c, int v);
extern void SetBg2Offset(int a, int b);
extern void func_02033bb8(int a);
extern void _ZN3G2x18SetBlendBrightnessEPVtts(void *p, unsigned short a, s16 b);
extern void func_02020304(void);

extern unsigned char data_0209f4ae[];
extern s16 data_ov075_0211b5d4[];
extern unsigned char data_0209d454[];
extern int data_ov075_0211c9b8[];
extern int data_ov075_0211d71c[];
extern unsigned char data_0209d45c[];

/* C view of include/dScEntry_c.h's dScEntry_c (a C++ class this C file
 * cannot include), with the header's names; only the fields used here.
 * Each mIcons entry is a dScEntry_c::icon_c, a 0x24-byte dThIcon_c. */
typedef struct dThIcon_c {
    unsigned char pad_00[0x10];
    unsigned char mOn; /* 0x10 */
    unsigned char pad_11[0x13];
} dThIcon_c;

typedef struct dScEntry_c {
    unsigned char pad_000[0x70];
    dThIcon_c mIcons[9]; /* 0x070 */
    unsigned char pad_1b4[0xb4];
    int mStepWork[4];             /* 0x268 */
    unsigned char pad_278[8];
    unsigned char mIconCount;     /* 0x280 */
    unsigned char mSelectedIcon;  /* 0x281 */
    unsigned char pad_282[6];
} dScEntry_c;

typedef char dScEntry_c_size_must_be_0x288[sizeof(dScEntry_c) == 0x288 ? 1 : -1];

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
    _ZN3G2x18SetBlendBrightnessEPVtts((void *)0x4000050, 0xb, ~5);

    scene->mStepWork[0] = scene->mSelectedIcon;
    func_02020304();
}
