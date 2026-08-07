/* AUTO-GENERATED from matched-function evidence by tools/gen_header.py
 * class Snowball: 5 matched functions, 18 evidenced fields.
 * Offsets/widths are observed, not guessed. Gaps are explicit padding.
 * Field NAMES are placeholders - renaming cannot change codegen. */
#ifndef SNOWBALL_H
#define SNOWBALL_H
#include "types.h"
#include "Model.h"
#include "MovingCylinderClsn.h"
#include "WithMeshClsn.h"
#include "ShadowModel.h"

struct Snowball {
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
    u8  pad_0a4[0x4];
    s32 unk_0a8;            /* 0x0a8 */
    s32 unk_0ac;            /* 0x0ac */
    u8  pad_0b0[0x50];
    u8  unk_100;            /* 0x100 */
    u8  pad_101[0xf];
    /* MovingCylinderClsn member, named by the class's own destructor calling
       MovingCylinderClsn's D1 at +0x110 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8SnowballD1Ev.c] */
    MovingCylinderClsn mMovingCylinderClsn;            /* 0x110 */
    /* WithMeshClsn member, named by the class's own destructor calling
       WithMeshClsn's D1 at +0x144 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8SnowballD1Ev.c] */
    WithMeshClsn mWithMeshClsn;            /* 0x144 */
    /* Model member, named by _ZN5ModelD1Ev at +0x300 -- a relocation the ROM build checks.
       D1 and not D2, so it is this type and not an inlined base. Was a u8 marker. */
    Model mModel;            /* 0x300 */
    /* ShadowModel member, named by the class's own destructor calling
       ShadowModel's D1 at +0x350 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8SnowballD1Ev.c] */
    ShadowModel mShadowModel;            /* 0x350 */
    s32 unk_378;            /* 0x378 */
    s32 unk_37c;            /* 0x37c */
    s32 unk_380;            /* 0x380 */
    s32 unk_384;            /* 0x384 */
#ifdef __cplusplus
    /* methods */
    int Behavior();
    int InitResources();
    int Render();
#endif
};

#endif
