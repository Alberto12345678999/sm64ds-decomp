//cpp
#include "dScEntry_c.h"
#include "types.h"

extern dScEntry_c::StepSet data_ov075_0211d810;
extern dScEntry_c::StepSet data_ov075_0211d888;
extern dScEntry_c::StepSet data_ov075_0211d8e8;
extern int data_ov075_0211d930;

extern "C" {

extern int func_0203da9c(void);
extern int TouchArea_Update(void* c, int id);
extern void func_ov001_020ab41c(void* c);
extern int func_0203d9b4(void);
extern void func_02030a78(void);
extern void func_02012790(int x);
extern void func_02030aa4(int arg);

static inline unsigned IsMode6(dScEntry_c *scene) {
    /* materialized: returning the comparison directly shrinks the caller (0x15c) */
    unsigned dok = (scene->actorID == 6);
    return dok;
}

void func_ov075_02117c0c(char* self)
{
    int id;
    dScEntry_c *scene = reinterpret_cast<dScEntry_c *>(self);

    id = func_0203da9c();
    if (TouchArea_Update(&scene->mIcons[0], id) != 0 ||
        (scene->CheckMenuConfirm(id) != 0 &&
         scene->mSelectedIcon == 0)) {
        scene->mIcons[1].mOn = 0;
        func_ov001_020ab41c(&scene->mIcons[0]);
        if (func_0203d9b4() != 0 && IsMode6(scene)) {
            scene->ChangeStepsAfterDelay(&data_ov075_0211d8e8, 0x14);
        } else {
            func_02030a78();
            scene->ChangeStepsAfterDelay(
                reinterpret_cast<const dScEntry_c::StepSet *>(&data_ov075_0211d930), 0x14);
        }
        func_02012790(0x63);
        return;
    }
    if (TouchArea_Update(&scene->mIcons[1], id) == 0) {
        if (scene->CheckMenuConfirm(id) == 0)
            return;
        if (scene->mSelectedIcon != 1)
            return;
    }
    scene->mIcons[0].mOn = 0;
    func_ov001_020ab41c(&scene->mIcons[1]);
    if (IsMode6(scene)) {
        scene->ChangeStepsAfterDelay(&data_ov075_0211d888, 0x14);
        func_02030aa4(3);
    } else {
        scene->ChangeStepsAfterDelay(&data_ov075_0211d810, 0x14);
    }
    func_02012790(0x98);
}
}
