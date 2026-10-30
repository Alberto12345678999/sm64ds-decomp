/* The 0x1c-byte animation player func_ov007_020c92ac allocates; names as in
 * func_ov007_020c9268, which resets it. */
typedef struct Ov007AnimPlayer {
    int state;                 /* 0x00: 0 playing, 1 held, 2 stopped */
    int loopMode;              /* 0x04: 0 one-shot, 1 wrap, 2 ping-pong */
    int flags;                 /* 0x08: bit 0 shows the start frame once */
    short anim;                /* 0x0c: -1 none */
    short prevAnim;            /* 0x0e */
    short frame;               /* 0x10 */
    unsigned short frameCount; /* 0x12 */
    int framePos;              /* 0x14: Q12 */
    int speed;                 /* 0x18: Q12 frames per tick */
} Ov007AnimPlayer;

/* Advances a player one tick. While playing, speed moves framePos; past
 * either end loopMode decides: one-shot stops, wrap jumps to the other end,
 * ping-pong negates speed and clamps. frame always follows framePos. */
void func_ov007_020c9110(Ov007AnimPlayer *p) {
    if (p->anim == -1)
        return;
    {
        int flags = p->flags;
        if ((flags & 1) == 0) {
            int last = (p->frameCount - 1) << 12;
            int hit = 0; /* 1 ran below 0, 2 ran past the last frame */
            switch (p->state) {
            case 0:
                p->framePos += p->speed;
                if (p->framePos > last)
                    hit = 2;
                else if (p->framePos < 0)
                    hit = 1;
                break;
            case 1:
                break;
            case 2:
                break;
            }
            if (hit != 0) {
                switch (p->loopMode) {
                case 0:
                    p->state = 2;
                    break;
                case 1:
                    if (hit == 1)
                        hit = 2;
                    else
                        hit = 1;
                    break;
                case 2:
                    p->speed *= -1;
                    break;
                }
                if (hit == 1)
                    last = 0;
                p->framePos = last;
            }
        } else {
            p->flags = flags & ~1;
        }
    }
    p->frame = p->framePos >> 12;
}
