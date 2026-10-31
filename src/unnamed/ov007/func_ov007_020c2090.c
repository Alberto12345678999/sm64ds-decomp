#include "Ov007Pad.h"

/* Zeroes every button's held and released frame counts, leaving keys, the
 * axes and inputLock as they are (func_ov007_020c22a0 clears those too). */
void func_ov007_020c2090(Ov007Pad *pad) {
    int i;
    for (i = 0; i < 12; i++) {
        pad->releasedFrames[i] = 0;
        pad->heldFrames[i] = pad->releasedFrames[i];
    }
}
