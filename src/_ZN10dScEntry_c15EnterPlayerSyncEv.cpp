//cpp
#include "dScEntry_c.h"

extern "C" {
int func_0203d974();
int LoadFile(int);
void func_ov075_02116030(void *, int);
void func_020338b0(int, int, short, int);
extern u8 data_0209d454;
extern int data_ov075_0211d71c[];
}

// @symbol _ZN10dScEntry_c15EnterPlayerSyncEv
void dScEntry_c::EnterPlayerSync() {
    // Download-play clients and non-host stations install the waiting screen.
    if (func_0203d974()) {
        data_0209d454 &= ~5;
        int screen = LoadFile(0x8409);
        func_ov075_02116030(data_ov075_0211d71c, screen);
        func_020338b0(0x225, 0xb0, 0x1d, -1);
        data_0209d454 |= 5;
        mIconCount = 0;
        mWaiting.wavePhase = 0;
        mWaiting.waveDelay = 120;
    }
    mStepPhase = 0;
    mWaiting.playerWaitTicks = 0;
    mWaiting.syncTicks = 0;
}
