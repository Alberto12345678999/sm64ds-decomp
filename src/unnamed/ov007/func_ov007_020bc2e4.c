/* The BTP header word this file reads, as dExtAnmTexPat_c.h spells it. */
typedef struct Ov007BtpHeader {
    unsigned short numFrames; /* 0x00 */
} Ov007BtpHeader;

/* The 0xa0-byte model record func_ov007_020bc6d4 allocates; names as there,
 * only the texture-pattern animation slots. */
typedef struct Ov007Model {
    char pad_00[0x2c];
    Ov007BtpHeader **texSeqAnims; /* 0x2c */
    void *texSeqAnim;             /* 0x30: the func_ov007_020c92ac player */
} Ov007Model;

/* Unprototyped, as in func_ov007_020bc3dc. */
extern void func_ov007_020c9214();

/* Starts texture-pattern animation i at startFrame, wrapping, at one frame
 * per tick; does nothing when the table has no file for i. */
void func_ov007_020bc2e4(void *c, int i, int startFrame) {
    Ov007Model *m = (Ov007Model *)c;
    Ov007BtpHeader *btp = m->texSeqAnims[i];
    if (btp == 0)
        return;
    func_ov007_020c9214(m->texSeqAnim, i, 1, btp->numFrames, startFrame, 0x1000);
}
