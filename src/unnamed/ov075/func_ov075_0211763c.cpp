//cpp
#include "dScEntry_c.h"
extern "C" {
extern int func_0203da9c(void);
extern int TouchArea_Update(void *p, int x);
extern void SetControllerMode(unsigned char mode);
extern void func_02020028(int a, unsigned char b);
extern void func_ov001_020ab41c(void *p);
extern void func_ov075_02116c38(void *self);
extern void func_02012790(int a);
extern void SetBg2Offset(int a, int b);
extern unsigned short data_020a0e5a[];

void func_ov075_0211763c(void *thiz) {
    dScEntry_c *scene = reinterpret_cast<dScEntry_c *>(thiz);
    int w = func_0203da9c();

    if (TouchArea_Update(&scene->mIcons[3], -1) != 0 ||
        TouchArea_Update(&scene->mIcons[4], -1) != 0 || (data_020a0e5a[w << 1] & 8) != 0 ||
        (data_020a0e5a[w << 1] & 4) != 0 ||
        (scene->CheckMenuConfirm(-1) != 0 && scene->mSelectedIcon == 3)) {
        int i;
        for (i = 0; i <= 2; i++) {
            if (scene->mIcons[i].mOn != 0) {
                SetControllerMode(i);
                func_02020028(w, i);
            }
        }
        func_ov001_020ab41c(&scene->mIcons[3]);
        scene->mSelectedIcon = 3;
        func_ov075_02116c38(scene);
        func_02012790(0x11a);
        return;
    }

    if (TouchArea_Update(&scene->mIcons[0], -1) != 0 ||
        (scene->CheckMenuConfirm(-1) != 0 && scene->mSelectedIcon == 0)) {
        scene->mSelectedIcon = 0;
        if (scene->mIcons[0].mOn != 0) {
            SetControllerMode(0);
            func_02020028(w, 0);
            func_ov075_02116c38(scene);
            func_02012790(0x11a);
        } else {
            scene->mIcons[1].mOn = 0;
            scene->mIcons[2].mOn = 0;
            scene->mStepWork[0] = scene->mSelectedIcon;
            SetBg2Offset(0, 0);
            func_02012790(0x5b);
        }
        func_ov001_020ab41c(&scene->mIcons[0]);
        return;
    }

    if (TouchArea_Update(&scene->mIcons[1], -1) != 0 ||
        (scene->CheckMenuConfirm(-1) != 0 && scene->mSelectedIcon == 1)) {
        scene->mSelectedIcon = 1;
        if (scene->mIcons[1].mOn != 0) {
            SetControllerMode(1);
            func_02020028(w, 1);
            func_ov075_02116c38(scene);
            func_02012790(0x11a);
        } else {
            scene->mIcons[0].mOn = 0;
            scene->mIcons[2].mOn = 0;
            scene->mStepWork[0] = scene->mSelectedIcon;
            SetBg2Offset(0x100, 0);
            func_02012790(0x5b);
        }
        func_ov001_020ab41c(&scene->mIcons[1]);
        return;
    }

    if (TouchArea_Update(&scene->mIcons[2], -1) != 0 ||
        (scene->CheckMenuConfirm(-1) != 0 && scene->mSelectedIcon == 2)) {
        scene->mSelectedIcon = 2;
        if (scene->mIcons[2].mOn != 0) {
            SetControllerMode(2);
            func_02020028(w, 2);
            func_ov075_02116c38(scene);
            func_02012790(0x11a);
        } else {
            scene->mIcons[0].mOn = 0;
            scene->mIcons[1].mOn = 0;
            scene->mStepWork[0] = scene->mSelectedIcon;
            SetBg2Offset(0, 0x100);
            func_02012790(0x5b);
        }
        func_ov001_020ab41c(&scene->mIcons[2]);
        return;
    }
}
}
