//cpp
#include "Fader.hpp"

int FaderBrightness::IsAtEnd()
{
    return currInterp == 0x1000;
}
