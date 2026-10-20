//cpp
#include "dScEntry_c.h"

namespace G2S {
u32 GetBG2ScrPtr();
u32 GetBG3ScrPtr();
}

extern "C" {
int func_0200f0bc();
u32 LoadCompressedFileAt(u16, void *);
int func_0203da9c();
int func_0203d974();
u32 func_02012790(u32);
extern u8 data_0209d454;
}

// @symbol _ZN10dScEntry_c22EnterPlayerSelectIntroEv
void dScEntry_c::EnterPlayerSelectIntro() {
    int row;
    int col;
    u16 *tiles;
    u32 palette;
    data_0209d454 &= ~5;
    if (func_0200f0bc() == 0)
        LoadCompressedFileAt(0x840a, reinterpret_cast<void *>(G2S::GetBG2ScrPtr()));
    else
        LoadCompressedFileAt(0x980c, reinterpret_cast<void *>(G2S::GetBG2ScrPtr()));
    LoadCompressedFileAt(0x840b, reinterpret_cast<void *>(G2S::GetBG3ScrPtr()));

    // Color the 9-by-10 tile panel for this player's wireless station.
    tiles = reinterpret_cast<u16 *>(G2S::GetBG2ScrPtr()) + 11 * 32 + 11;
    palette = (static_cast<u32>(func_0203da9c() + 10) << 28) >> 16;
    for (row = 0; row < 10; ++row) {
        for (col = 0; col < 9; ++col)
            tiles[col] = palette | (tiles[col] & 0xfff);
        tiles += 32;
    }
    data_0209d454 |= 4;
    mIconCount = 0;
    mStepDelay = 180;
    if (func_0203d974()) {
        mStepPhase = 0;
        mPlayerSelectReady = 0;
        mWaiting.syncTicks = 0;
    } else {
        mStepPhase = 1;
    }
    func_02012790(0x122);
}
