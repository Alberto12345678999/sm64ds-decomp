#include "Ov007Model.h"

/* The BTA header word this file reads, as dExtAnmTexSRT_c.h spells it: a
 * partial C view of a tag that header defines only for C++. */
struct BTA_File {
    unsigned short numFrames; /* 0x00 */
};

/* Unprototyped, as in func_ov007_020bc3dc. */
extern void func_ov007_020c9214();

/* Starts texture-SRT animation i at startFrame, wrapping, at one frame per
 * tick; does nothing when the table has no file for i. */
void func_ov007_020bc32c(Ov007Model *m, int i, int startFrame) {
    struct BTA_File *bta = m->texSrtAnims[i];
    if (bta == 0)
        return;
    func_ov007_020c9214(m->texSrtAnim, i, 1, bta->numFrames, startFrame, 0x1000);
}
