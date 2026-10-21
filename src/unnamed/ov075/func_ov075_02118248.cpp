//cpp
#include "dScEntry_c.h"
#include "types.h"

extern int data_ov075_0211d870[];
extern dScEntry_c::StepSet data_ov075_0211d8b8;

extern "C" {
extern u8 data_0209fc58;
extern dScEntry_c::StepSet data_ov075_0211d810;

extern void func_ov075_02119dc4(int a, int* data);
extern int func_0203da9c(void);
extern int TouchArea_Update(void* c, int id);
extern void func_ov001_020ab41c(void* c);
extern void func_02012790(int x);

/* dScEntry_c as this step reads it; mIcons follows dScEntry_c.h. An icon's
 * byte 0x10 is dThIcon_c::mOn, the lit flag that func_ov001_020ab5b0 clears,
 * dThIcon_c::Behavior toggles when its countdown expires, and
 * func_ov001_020ab41c sets when clear. mSelectedIcon (0x281) is the icon the
 * pad picks: func_ov075_02117918 loads it from the player's save slot, lights
 * mIcons[mSelectedIcon] and picks the BG2 panel from it, and a confirm press
 * (CheckMenuConfirm) acts on the icon it names. */
typedef struct EntryIcon {
    u8 pad_00[0x10];
    u8 mOn; /* 0x10 */
    u8 pad_11[0x13];
} EntryIcon;

typedef struct EntryScene {
    u8 pad_000[0x70];
    EntryIcon mIcons[9]; /* 0x070 */
    u8 pad_1b4[0xcd];
    u8 mSelectedIcon; /* 0x281 */
} EntryScene;

void func_ov075_02118248(char* self)
{
    EntryScene *scene = (EntryScene *)self;
    int id;
    if (data_0209fc58 != 0) {
        func_ov075_02119dc4((int)self, reinterpret_cast<int *>(&data_ov075_0211d810));
        return;
    }
    id = func_0203da9c();
    if (TouchArea_Update(&scene->mIcons[0], id) != 0 ||
        (reinterpret_cast<dScEntry_c *>(self)->CheckMenuConfirm(id) != 0 &&
         scene->mSelectedIcon == 0)) {
        scene->mIcons[1].mOn = 0;
        func_ov001_020ab41c(&scene->mIcons[0]);
        reinterpret_cast<dScEntry_c *>(self)->ChangeStepsAfterDelay(
            reinterpret_cast<const dScEntry_c::StepSet *>(data_ov075_0211d870), 0x14);
        func_02012790(0x126);
        return;
    }
    if (TouchArea_Update(&scene->mIcons[1], id) == 0) {
        if (reinterpret_cast<dScEntry_c *>(self)->CheckMenuConfirm(id) == 0)
            return;
        if (scene->mSelectedIcon != 1)
            return;
    }
    scene->mIcons[0].mOn = 0;
    func_ov001_020ab41c(&scene->mIcons[1]);
    reinterpret_cast<dScEntry_c *>(self)->ChangeStepsAfterDelay(&data_ov075_0211d8b8, 0x14);
    func_02012790(0x119);
}
}
