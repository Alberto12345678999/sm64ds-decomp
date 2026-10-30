/* A sprite bank's 0x10-byte cell animation; frames and durations as
 * func_ov007_020c9688 fills them and func_ov007_020c0d70 steps through
 * them. The two halfwords at +8 have no reader found (func_ov007_020c9688
 * passes 0 for both). */
typedef struct Ov007CellAnim {
    void **frames;             /* 0x00: one cell pointer per frame */
    unsigned short *durations; /* 0x04: ticks per frame */
    short word8;               /* 0x08 */
    short wordA;               /* 0x0a */
    int frameCount;            /* 0x0c */
} Ov007CellAnim;

extern void *func_ov007_020c3df4(int a, int b);

/* Allocates a cell animation's frame and duration tables for `frameCount`
 * frames. */
void func_ov007_020c13a4(char *c, int frameCount, short a, short b) {
    Ov007CellAnim *anim = (Ov007CellAnim *)c;
    anim->frames = (void **)func_ov007_020c3df4(0, frameCount * 4);
    anim->durations = (unsigned short *)func_ov007_020c3df4(0, frameCount * 2);
    anim->frameCount = frameCount;
    anim->word8 = a;
    anim->wordA = b;
}
