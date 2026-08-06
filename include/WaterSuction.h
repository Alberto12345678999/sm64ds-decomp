/* AUTO-GENERATED from matched-function evidence by tools/gen_header.py
 * class WaterSuction: 4 matched functions, 11 evidenced fields.
 * Offsets/widths are observed, not guessed. Gaps are explicit padding.
 * Field NAMES are placeholders - renaming cannot change codegen. */
#ifndef WATERSUCTION_H
#define WATERSUCTION_H
#include "types.h"
#include "MovingCylinderClsnWithPos.h"

struct WaterSuction {
    u8  pad_000[0x8];
    s32 unk_008;            /* 0x008 */
    u8  pad_00c[0x80];
    s16 unk_08c;            /* 0x08c */
    s16 unk_08e;            /* 0x08e */
    s16 unk_090;            /* 0x090 */
    s16 unk_092;            /* 0x092 */
    s16 unk_094;            /* 0x094 */
    s16 unk_096;            /* 0x096 */
    u8  pad_098[0x68];
    u8  unk_100;            /* 0x100 */
    u8  pad_101[0xf];
    /* MovingCylinderClsnWithPos member, named by the class's own destructor calling
       MovingCylinderClsnWithPos's D1 at +0x110 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN12WaterSuctionD1Ev.c] */
    MovingCylinderClsnWithPos mMovingCylinderClsnWithPos;            /* 0x110 */
    u8  mWithMeshClsn;            /* 0x150 */
    u8  pad_151[0x1c3];
    s32 unk_314;            /* 0x314 */
#ifdef __cplusplus
    /* methods */
    int Behavior();
    int InitResources();
#endif
};

#endif
