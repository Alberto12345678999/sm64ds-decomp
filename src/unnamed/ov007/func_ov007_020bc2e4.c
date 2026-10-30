#include "Ov007Model.h"

/* The BTP header word this file reads, as dExtAnmTexPat_c.h spells it. */
struct BTP_File {
    unsigned short numFrames; /* 0x00 */
};

/* Unprototyped, as in func_ov007_020bc3dc. */
extern void func_ov007_020c9214();

/* Starts texture-pattern animation i at startFrame, wrapping, at one frame
 * per tick; does nothing when the table has no file for i. */
void func_ov007_020bc2e4(Ov007Model *m, int i, int startFrame) {
    struct BTP_File *btp = m->texSeqAnims[i];
    if (btp == 0)
        return;
    func_ov007_020c9214(m->texSeqAnim, i, 1, btp->numFrames, startFrame, 0x1000);
}
