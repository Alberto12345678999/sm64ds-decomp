/* AUTO-GENERATED from matched-function evidence by tools/gen_header.py
 * class HeaveHo: 5 matched functions, 24 evidenced fields.
 * Offsets/widths are observed, not guessed. Gaps are explicit padding.
 * Field NAMES are placeholders - renaming cannot change codegen. */
#ifndef HEAVEHO_H
#define HEAVEHO_H
#include "types.h"
#include "MovingCylinderClsn.h"
#include "MovingCylinderClsnWithPos.h"
#include "WithMeshClsn.h"

struct HeaveHo {
    u8  pad_000[0x5c];
    s32 mPosX;            /* 0x05c */
    s32 mPosY;            /* 0x060 */
    s32 mPosZ;            /* 0x064 */
    u8  pad_068[0x26];
    s16 mAngleY;            /* 0x08e */
    u8  pad_090[0x4];
    s16 mPrevAngleY;            /* 0x094 */
    u8  pad_096[0x6];
    s32 unk_09c;            /* 0x09c */
    s32 unk_0a0;            /* 0x0a0 */
    u8  pad_0a4[0x5c];
    u8  unk_100;            /* 0x100 */
    u8  pad_101[0xf];
    /* MovingCylinderClsn member, named by the class's own destructor calling
       MovingCylinderClsn's D1 at +0x110 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN7HeaveHoD1Ev.c] */
    MovingCylinderClsn mMovingCylinderClsn;            /* 0x110 */
    /* MovingCylinderClsnWithPos member, named by the class's own destructor calling
       MovingCylinderClsnWithPos's D1 at +0x144 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN7HeaveHoD1Ev.c] */
    MovingCylinderClsnWithPos mMovingCylinderClsnWithPos;            /* 0x144 */
    /* WithMeshClsn member, named by the class's own destructor calling
       WithMeshClsn's D1 at +0x184 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN7HeaveHoD1Ev.c] */
    WithMeshClsn mWithMeshClsn;            /* 0x184 */
    u8  mModelAnim;            /* 0x340 */
    u8  pad_341[0x4f];
    u8  mAnimation;            /* 0x390 */
    u8  pad_391[0xb];
    s32 unk_39c;            /* 0x39c */
    u8  pad_3a0[0x4];
    u8  mShadowModel;            /* 0x3a4 */
    u8  pad_3a5[0x57];
    s32 unk_3fc;            /* 0x3fc */
    s32 unk_400;            /* 0x400 */
    s32 unk_404;            /* 0x404 */
    s32 unk_408;            /* 0x408 */
    s32 unk_40c;            /* 0x40c */
    s32 unk_410;            /* 0x410 */
    s32 unk_414;            /* 0x414 */
    s32 unk_418;            /* 0x418 */
    u8  pad_41c[0xa];
    u8  unk_426;            /* 0x426 */
#ifdef __cplusplus
    /* methods */
    int Behavior();
    int InitResources();
    int Render();
#endif
};

#endif
