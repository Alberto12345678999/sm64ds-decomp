//cpp
#include "types.h"
#include "G2.h"
#include "G2x.h"
#include "Message.h"
#include "Sound.h"
#include "dScEntry_c.h"

extern "C" {

extern void func_ov075_02116028(int *p, int v);
extern int LoadFile(int handle);
extern void func_ov075_02116030(void *c, int v);
extern unsigned int LoadCompressedFileAt(u16 fileID, void *target);
extern void func_ov075_02115e8c(void *p, int b, int c, int d, int e);
extern void func_02020190(void);

extern unsigned char data_0209d454;
extern int data_ov075_0211d71c;
extern unsigned char data_0209d45c;
extern int data_0209fc68;

/* A dScEntry_c::Step. It sets data_0209d45c bits 0xe and records them in
 * mDisconnectHideMask; on a player disconnect
 * dScEntry_c::HandlePlayerDisconnect clears data_0209d45c by
 * ~mDisconnectHideMask, and func_ov075_02117e84 clears both on its own. */

void func_ov075_02118378(void *c) {
    dScEntry_c *scene = (dScEntry_c *)c;

    data_0209d454 &= ~5;
    func_ov075_02116028(&data_ov075_0211d71c, 1);
    func_ov075_02116030(&data_ov075_0211d71c, LoadFile(0x9801));
    LoadCompressedFileAt(0x8407, G2S::GetBG3ScrPtr());
    Message::DisplayVsExitText(0x1f);

    data_0209d45c |= 0xe;
    data_0209d454 |= 5;
    scene->mSelectedIcon = 0;
    func_ov075_02115e8c(&scene->mIcons[0], 0xa, 0, 0x80, 0x48);
    func_ov075_02115e8c(&scene->mIcons[1], 0xa, 0, 0x80, 0x78);
    scene->mIconCount = 2;
    G2x::SetBlendAlpha((volatile unsigned short *)0x4000050, 4, 0x11, 0xc, 4);
    scene->mDisconnectHideMask = 0xe;
    if (data_0209fc68 != 0)
        data_0209fc68 = 5;
    func_02020190();
    scene->mStepWork[0] = 0;
    scene->mStepWork[1] = 0;
    func_02012790(0x125);
    Sound::LoadAndSetMusic_Layer1(0x4c);
}
}
