/* AUTO-GENERATED from matched-function evidence by tools/gen_header.py
 * class BigBully: 5 matched functions, 18 evidenced fields.
 * Offsets/widths are observed, not guessed. Gaps are explicit padding.
 * Field NAMES are placeholders - renaming cannot change codegen. */
#ifndef BIGBULLY_H
#define BIGBULLY_H
#include "types.h"
#include "ModelAnim.h"
#include "WithMeshClsn.h"
#include "MovingCylinderClsn.h"

struct BigBully {
    u8  pad_000[0x4];
    s32 unk_004;            /* 0x004 */
    s32 mParam;            /* 0x008 */
    u8  pad_00c[0x50];
    s32 mPosX;            /* 0x05c */
    s32 mPosY;            /* 0x060 */
    s32 mPosZ;            /* 0x064 */
    u8  pad_068[0x34];
    s32 unk_09c;            /* 0x09c */
    s32 unk_0a0;            /* 0x0a0 */
    u8  pad_0a4[0x4];
    s32 unk_0a8;            /* 0x0a8 */
    u8  pad_0ac[0x20];
    s8  mAreaId;            /* 0x0cc */
    u8  pad_0cd[0x43];
    /* ModelAnim member, named by _ZN9ModelAnimD1Ev at +0x110 -- a relocation the ROM build checks.
       D1 and not D2, so it is this type and not an inlined base. Was a u8 marker. */
    ModelAnim mModelAnim;            /* 0x110 */
    /* WithMeshClsn member, named by the class's own destructor calling
       WithMeshClsn's D1 at +0x174 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8BigBullyD1Ev.c] */
    WithMeshClsn mWithMeshClsn;            /* 0x174 */
    u8  unk_330;            /* 0x330 */
    u8  pad_331[0xb];
    /* MovingCylinderClsn member, named by the class's own destructor calling
       MovingCylinderClsn's D1 at +0x33c -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8BigBullyD1Ev.c] */
    MovingCylinderClsn mMovingCylinderClsn;            /* 0x33c */
    u8  mShadowModel;            /* 0x370 */
    u8  pad_371[0x89];
    u16 mSecretSoundCounter;            /* 0x3fa */
    u8  unk_3fc;            /* 0x3fc */
    u8  unk_3fd;            /* 0x3fd */
    u8  unk_3fe;            /* 0x3fe */
#ifdef __cplusplus
    /* methods */
    int Behavior();
    int InitResources();
    int Render();
#endif
};

#endif
