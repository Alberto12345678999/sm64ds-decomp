//cpp
#include "types.h"
#include "Sound.h"

extern "C" {

extern s32 data_02099fb0;

void func_02048e74(void) {
    data_02099fb0 = 4;
    Sound::Player::SetPlayableSeqCount(9, 4);
}
}
