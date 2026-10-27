//cpp
#include "Sound.h"

extern "C" {

extern int data_02099fb0;

void func_02048e94(void) {
    data_02099fb0 = 4;
    Sound::Player::SetPlayableSeqCount(9, 4);
}
}
