//cpp
#include "dScEntry_c.h"
#include "types.h"
#include "Sound.h"

extern dScEntry_c::StepSet data_ov075_0211d870;
extern dScEntry_c::StepSet data_ov075_0211d8b8;

extern "C" {
extern u8 data_0209fc58;
extern dScEntry_c::StepSet data_ov075_0211d810;

extern int func_0203da9c(void);
extern int TouchArea_Update(void* c, int id);
extern void func_ov001_020ab41c(void* c);

void func_ov075_02118248(char* self)
{
    dScEntry_c *scene = reinterpret_cast<dScEntry_c *>(self);
    int id;
    if (data_0209fc58 != 0) {
        scene->HandlePlayerDisconnect(&data_ov075_0211d810);
        return;
    }
    id = func_0203da9c();
    if (TouchArea_Update(&scene->mIcons[0], id) != 0 ||
        (scene->CheckMenuConfirm(id) != 0 && scene->mSelectedIcon == 0)) {
        scene->mIcons[1].mOn = 0;
        func_ov001_020ab41c(&scene->mIcons[0]);
        scene->ChangeStepsAfterDelay(&data_ov075_0211d870, 0x14);
        func_02012790(0x126);
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
    scene->ChangeStepsAfterDelay(&data_ov075_0211d8b8, 0x14);
    func_02012790(0x119);
}
}
