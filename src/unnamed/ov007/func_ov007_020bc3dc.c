/* The BCA header fields this file reads; dExtFrameCtrl_c::UpdateFileOffsets
 * spells the rest. The byte at +4 selects func_ov007_020c9214's loop mode
 * below: zero plays once, nonzero wraps. */
typedef struct Ov007BcaHeader {
    char pad_00[2];
    unsigned short numFrames; /* 0x02 */
    unsigned char looping;    /* 0x04 */
} Ov007BcaHeader;

/* The 0xa0-byte model record func_ov007_020bc6d4 allocates; names as there,
 * only the bone-animation slots. */
typedef struct Ov007Model {
    char pad_00[0x14];
    Ov007BcaHeader **boneAnims; /* 0x14 */
    void *boneAnim;             /* 0x18: the func_ov007_020c92ac player */
} Ov007Model;

/* Unprototyped, as the tree has it: a prototype with the definition's short
 * parameters adds sign-extensions the ROM does not have. */
extern void func_ov007_020c9214();

/* func_ov007_020c9214's loopMode values used here (see func_ov007_020c9110). */
enum Ov007LoopMode { LOOP_ONCE, LOOP_WRAP };

/* Starts bone animation i at startFrame, at one frame per tick; does nothing
 * when the table has no file for i. */
void func_ov007_020bc3dc(void *c, int i, int startFrame) {
    Ov007Model *m = (Ov007Model *)c;
    Ov007BcaHeader *bca = m->boneAnims[i];
    enum Ov007LoopMode loopMode;
    if (bca == 0)
        return;
    loopMode = (bca->looping == 0) ? LOOP_ONCE : LOOP_WRAP;
    func_ov007_020c9214(m->boneAnim, i, loopMode, bca->numFrames, startFrame, 0x1000);
}
