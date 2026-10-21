//cpp
#include "dScEntry_c.h"
#include "types.h"
#include "PlayerInput.h"

extern dScEntry_c::StepSet data_ov075_0211d798;
extern dScEntry_c::StepSet data_ov075_0211d7f8;

extern "C" {
extern int func_0203d974(void);
extern u8 func_020202dc(void);
extern u8 func_02020168(void);
extern void func_02020304(void);
extern void func_020200e0(void);
extern u8 func_020200b8(void);
extern void func_ov001_020ab3f0(void *r0);
extern u32 func_02012790(u32 a);
extern int func_0203d9b4(void);
extern int TouchArea_Update(char *p, int i);
extern void func_02020078(u32 flags);
extern void func_02020124(void);
extern void func_0202029c(u32 idx);
extern int func_0203da9c(void);
extern u8 data_0209b2e4;
extern u16 data_020a0e5a[];
}
void dScEntry_c::UpdateCourseSelect() {
    if (func_0203d974() && func_020202dc() != data_0209b2e4) {
        data_0209b2e4 = func_020202dc();
    }
    if (func_02020168()) {
        u8 action;
        func_02020304();
        func_020200e0();
        action = func_020200b8();
        if (action == 0) {
            int index;
            func_ov001_020ab3f0(&mIcons[data_0209b2e4]);
            mIcons[data_0209b2e4].mReady = 0;
            index = 0;
            for (; index < 4; index++) {
                if (index != data_0209b2e4)
                    mIcons[index].mOn = 0;
            }
            SetSteps(&EntryMatchLoadingSteps);
            func_02012790(0xa0);
            func_02012790(0x128);
            return;
        }
        if (action == 1) {
            SetSteps(&data_ov075_0211d798);
            func_02012790(0x9e);
            return;
        }
        SetSteps(&data_ov075_0211d7f8);
        func_02012790(0x9f);
        return;
    }
    if (func_0203d9b4()) {
        if (ArePlayersReady()) {
            bool touched;
            int index;
            touched = false;
            index = 0;
            icon_c *icon = mIcons;
            for (; index < 4; index++) {
                if (TouchArea_Update((char *)icon, 0)) {
                    touched = true;
                    data_0209b2e4 = index;
                    break;
                }
                ++icon;
            }
            if (touched) {
                func_02020078(0);
                func_02020124();
            } else {
                if (data_020a0e5a[gActivePlayerSlot * 2] & 4) {
                    func_02020078(1);
                    func_02020124();
                } else if (data_020a0e5a[gActivePlayerSlot * 2] & 8) {
                    func_02020078(2);
                    func_02020124();
                }
            }
            func_0202029c(data_0209b2e4);
        }
    }
    *(u16 *)0x4000050 = 0;
    if (data_020a0e5a[func_0203da9c() * 2] & ~0xc) {
        func_02012790(0xe);
    }
}
