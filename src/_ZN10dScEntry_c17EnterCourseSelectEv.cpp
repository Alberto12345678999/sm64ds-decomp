//cpp
#include "dScEntry_c.h"
namespace G2S {
u32 GetBG3ScrPtr();
}
extern "C" {

extern void func_ov075_02116028(int *icon, int v);
extern int LoadFile(int handle);
extern void func_ov075_02116030(void *c, int v);

extern unsigned int LoadCompressedFileAt(u16 fileID, void *target);
extern int func_0203d9b4(void);
extern void func_020338b0(int a, int b, short c, int d);
extern void func_ov075_02115e8c(char *self, int a, int b, short c, short e);
extern void func_02020334(void);
extern void func_020200e0(void);

extern unsigned char data_0209d45c;
extern unsigned char data_0209d454;
extern int data_ov075_0211d71c;
extern unsigned char data_0209b2e4;
}
void dScEntry_c::EnterCourseSelect() {
    int index;
    int x;
    icon_c *icon;

    data_0209d45c &= ~4;
    data_0209d454 &= ~5;
    func_ov075_02116028(&data_ov075_0211d71c, 1);
    func_ov075_02116030(&data_ov075_0211d71c, LoadFile(0x8409));
    LoadCompressedFileAt(0x8407, (void *)G2S::GetBG3ScrPtr());

    if (func_0203d9b4() != 0)
        func_020338b0(0x205, 0xb0, 0x21, -1);
    else
        func_020338b0(0x225, 0xb0, 0x1d, -1);

    data_0209d454 |= 5;

    icon = mIcons;
    index = 0;
    x = 0x20;
    for (; index < 4; index++) {
        func_ov075_02115e8c((char *)icon, 7, index, (short)x, 0x48);
        mIcons[index].mOn = 1;
        mIcons[index].mPressTime = 8;
        x += 0x40;
        ++icon;
    }

    data_0209b2e4 = 4;
    func_ov075_02115e8c((char *)&mIcons[4], 0xd, 4, 0x80, -0x14);
    mIconCount = 5;
    func_02020334();
    func_020200e0();
}
