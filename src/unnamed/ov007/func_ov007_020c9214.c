/* The 0x1c-byte animation player func_ov007_020c92ac allocates; names as in
 * func_ov007_020c9268, which resets it. */
typedef struct Ov007AnimPlayer {
    int state;        /* 0x00: 0 playing, 1 held, 2 stopped */
    int loopMode;     /* 0x04: 0 one-shot, 1 wrap, 2 ping-pong */
    int flags;        /* 0x08: bit 0 shows the start frame once */
    short anim;       /* 0x0c: -1 none */
    short prevAnim;   /* 0x0e */
    short frame;      /* 0x10 */
    short frameCount; /* 0x12 */
    int framePos;     /* 0x14: Q12 */
    int speed;        /* 0x18: Q12 frames per tick */
} Ov007AnimPlayer;

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
