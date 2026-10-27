//cpp
#include "types.h"
#include "Sound.h"

extern "C" {

extern void* data_020890a0;

extern void RunKuppaScript(void* script);

void StartIntroCutscene(void)
{
    Sound::LoadInitialGroup(0x25);
    RunKuppaScript(&data_020890a0);
}
}
