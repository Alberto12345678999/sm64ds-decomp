#include "types.h"

/* The 0x44-byte OAM sprite node func_ov007_020c11ac allocates; names as in
 * func_ov007_020c10ec, only the slots this file touches. */
typedef struct Ov007OamNode {
    char pad_00[0x20];
    int mode;    /* 0x20: 0 = stopped, 1 = looping, else once */
    int rev;     /* 0x24: 1 = step backwards */
    int paused;  /* 0x28: no step while set */
    short frame; /* 0x2c */
    short tick;  /* 0x2e: ticks into the frame */
    int changed; /* 0x30: set when the frame wraps or clamps at an end */
} Ov007OamNode;

/* A sprite bank's 0x10-byte cell animation (func_ov007_020c13a4); only
 * the slots this file reads. */
typedef struct Ov007CellAnim {
    void **frames;  /* 0x00 */
    u16 *durations; /* 0x04: ticks per frame */
    char pad_08[4];
    u32 frameCount; /* 0x0c */
} Ov007CellAnim;

/* Steps the node's animation one tick forwards (or backwards when rev is
 * 1): past a frame's duration it moves to the next frame, and past either
 * end it wraps (looping) or clamps (once) and sets `changed`. */
void func_ov007_020c0d70(Ov007OamNode *a, Ov007CellAnim *d) {
    int loop;
    int step;
    short m;
    int dur;

    if (a->mode == 0)
        return;
    if (a->paused != 0)
        return;

    step = 1;
    loop = (a->mode == 1);
    a->paused = 0;
    a->changed = 0;
    if (a->rev == 1) {
        m = -1;
        step = step * m;
    }

    a->tick += step;

    dur = d->durations[a->frame];
    if (a->tick >= dur) {
        a->tick = 0;
        a->frame += 1;
        if (a->frame < d->frameCount)
            return;
        a->frame = loop ? 0 : d->frameCount - 1;
        a->changed = 1;
    } else if (a->tick < 0) {
        a->tick = dur - 1;
        a->frame -= 1;
        if (a->frame >= 0)
            return;
        a->frame = loop ? d->frameCount - 1 : 0;
        a->changed = 1;
    }
}
