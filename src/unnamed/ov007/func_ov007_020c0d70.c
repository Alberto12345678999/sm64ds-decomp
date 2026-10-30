#include "Ov007OamNode.h"

/* Steps the node's animation one tick forwards (or backwards when rev is
 * 1): past a frame's duration it moves to the next frame, and past either
 * end it wraps (looping) or clamps (once) and sets `changed`. */
void func_ov007_020c0d70(Ov007OamNode *node, Ov007CellAnim *anim) {
    int loop;
    int step;
    short m;
    int dur;

    if (node->mode == 0)
        return;
    if (node->paused != 0)
        return;

    step = 1;
    loop = (node->mode == 1);
    node->paused = 0;
    node->changed = 0;
    if (node->rev == 1) {
        m = -1;
        step = step * m;
    }

    node->tick += step;

    dur = anim->durations[node->frame];
    if (node->tick >= dur) {
        node->tick = 0;
        node->frame += 1;
        if (node->frame < anim->frameCount)
            return;
        node->frame = loop ? 0 : anim->frameCount - 1;
        node->changed = 1;
    } else if (node->tick < 0) {
        node->tick = dur - 1;
        node->frame -= 1;
        if (node->frame >= 0)
            return;
        node->frame = loop ? anim->frameCount - 1 : 0;
        node->changed = 1;
    }
}
