//cpp
#include "Fader.hpp"

/* Snaps the fade to its end: 1.0 in 20.12 fixed point. */
void FaderBrightness::SetToEnd()
{
    currInterp = 0x1000;
}
