/* The BTA header word this file reads, as dExtAnmTexSRT_c.h spells it. */
typedef struct Ov007BtaHeader {
    unsigned short numFrames; /* 0x00 */
} Ov007BtaHeader;

/* The 0xa0-byte model record func_ov007_020bc6d4 allocates; names as there,
 * only the texture-SRT animation slots. */
typedef struct Ov007Model {
    char pad_00[0x20];
    Ov007BtaHeader **texSrtAnims; /* 0x20 */
    void *texSrtAnim;             /* 0x24: the func_ov007_020c92ac player */
} Ov007Model;

/* Unprototyped, as in func_ov007_020bc3dc. */
extern void func_ov007_020c9214();

/* Starts texture-SRT animation i at startFrame, wrapping, at one frame per
 * tick; does nothing when the table has no file for i. */
void func_ov007_020bc32c(void *c, int i, int startFrame) {
    Ov007Model *m = (Ov007Model *)c;
    Ov007BtaHeader *bta = m->texSrtAnims[i];
    if (bta == 0)
        return;
    func_ov007_020c9214(m->texSrtAnim, i, 1, bta->numFrames, startFrame, 0x1000);
}
