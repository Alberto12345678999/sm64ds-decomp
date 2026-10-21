//cpp
#include "dScEntry_c.h"
#include "Sound.h"
extern "C" {
void PrepareVsMode(void);
void LoadLevelNoReturn(int levelID, u32 entranceID, u32 mode, u32 arg3);
extern u8 data_0209b2e4;
extern s8 data_ov075_0211c6ec[];
extern u8 data_02092778;
}
void dScEntry_c::StartMatch() {
    PrepareVsMode();
    u8 course = data_0209b2e4;
    LoadLevelNoReturn(data_ov075_0211c6ec[course], 0, 2, 0);
    Sound::StopLoadedMusic_Layer1(0x3c);
    data_02092778 = 1;
}
