#include "Ov007Model.h"

/* Starts animation `anim` (frameCount frames long) at startFrame: playing,
 * with the old animation kept in prevAnim and the start frame held for one
 * func_ov007_020c9110 tick. */
void func_ov007_020c9214(Ov007AnimPlayer *p, short anim, int loopMode, short frameCount,
                         int startFrame, int speed) {
    p->state = 0;
    p->loopMode = loopMode;
    p->prevAnim = p->anim;
    p->anim = anim;
    p->frame = (short)startFrame;
    p->frameCount = frameCount;
    p->framePos = startFrame << 12;
    p->speed = speed;
    /* The const view is load-bearing: plain `p->flags |= 1` does not
     * match. */
    p->flags = ((const Ov007AnimPlayer *)p)->flags | 1;
}
