//cpp
#include "dScEntry_c.h"

extern "C" {
int Sound_PlayIfNotActive(int, int, int, int);
int func_0203d890();
void func_020308b4(int);
int func_020308a8();
int func_0203d8fc();
void func_ov075_0211a100(char *, int);
u32 func_02012790(u32);
extern u8 data_0209fc50;
extern u8 data_0209fc54;
extern u8 data_0208f274;
extern u8 data_ov075_0211d768[];
}

// @symbol _ZN10dScEntry_c16UpdatePlayerSyncEv
void dScEntry_c::UpdatePlayerSync() {
    mSoundHandle = Sound_PlayIfNotActive(mSoundHandle, 2, 0x11d, 0);

    switch (mStepPhase) {
    case 0: {
        u8 activePlayers = data_0209fc50;
        int sessionPlayers = func_0203d890();
        if (activePlayers == sessionPlayers) {
            func_020308b4(sessionPlayers);
            ++mStepPhase;
        } else {
            ++mWaiting.playerWaitTicks;
            if (mWaiting.playerWaitTicks >= 900)
                data_0209fc54 = 1;
        }
        break;
    }
    case 1:
        if (func_020308a8())
            ++mStepPhase;
        break;
    case 2: {
        int hostReady = func_0203d8fc();
        if (hostReady) {
            func_020308b4(hostReady);
            ++mStepPhase;
        }
        break;
    }
    case 3:
        if (func_020308a8()) {
            func_ov075_0211a100((char *)this, (int)data_ov075_0211d768);
            u8 observedPlayers = data_0208f274;
            int sessionPlayers = func_0203d890();
            if (observedPlayers == sessionPlayers) {
                func_02012790(0x11f);
                return;
            }
        }
        break;
    }

    if (mStepPhase < 1)
        return;
    ++mWaiting.syncTicks;
    if (mWaiting.syncTicks >= 2700)
        data_0209fc54 = 1;
}
