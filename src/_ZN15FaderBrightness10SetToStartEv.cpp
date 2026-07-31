//cpp
#include "Fader.hpp"

/* Snaps the fade to its start: 0.0 in 20.12 fixed point. */
void FaderBrightness::SetToStart()
{
    currInterp = 0;
}
