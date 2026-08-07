/* AUTO-GENERATED from matched-function evidence by tools/gen_header.py
 * class Pokey: 7 matched functions, 23 evidenced fields.
 * Offsets/widths are observed, not guessed. Gaps are explicit padding.
 * Field NAMES are placeholders - renaming cannot change codegen. */
#ifndef POKEY_H
#define POKEY_H
#include "types.h"
#include "Model.h"
#include "ShadowModel.h"
#include "MovingCylinderClsn.h"
#include "WithMeshClsn.h"

struct Pokey {
    u8  pad_000[0x8];
    u32 mParam;            /* 0x008 */
    u16 mActorID;            /* 0x00c */
    u8  pad_00e[0x4e];
    s32 mPosX;            /* 0x05c */
    s32 mPosY;            /* 0x060 */
    s32 mPosZ;            /* 0x064 */
    u8  pad_068[0x18];
    s32 mScaleX;            /* 0x080 */
    s32 mScaleY;            /* 0x084 */
    s32 mScaleZ;            /* 0x088 */
    u8  pad_08c[0xc];
    s32 unk_098;            /* 0x098 */
    s32 unk_09c;            /* 0x09c */
    s32 unk_0a0;            /* 0x0a0 */
    u8  pad_0a4[0x30];
    /* Model member, named by _ZN5ModelD1Ev at +0xd4 -- a relocation the ROM build checks.
       D1 and not D2, so it is this type and not an inlined base. Was a u8 marker. */
    Model mModel;            /* 0x0d4 */
    /* ShadowModel member, named by the class's own destructor calling
       ShadowModel's D1 at +0x124 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN5PokeyD0Ev.c] */
    ShadowModel mShadowModel;            /* 0x124 */
    /* MovingCylinderClsn member, named by the class's own destructor calling
       MovingCylinderClsn's D1 at +0x14c -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN5PokeyD0Ev.c] */
    MovingCylinderClsn mMovingCylinderClsn;            /* 0x14c */
    /* WithMeshClsn member, named by the class's own destructor calling
       WithMeshClsn's D1 at +0x180 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN5PokeyD0Ev.c] */
    WithMeshClsn mWithMeshClsn;            /* 0x180 */
    u8  unk_33c;            /* 0x33c */
    u8  pad_33d[0x2f];
    s32 unk_36c;            /* 0x36c */
    s32 unk_370;            /* 0x370 */
    s32 unk_374;            /* 0x374 */
    u8  pad_378[0x14];
    s32 unk_38c;            /* 0x38c */
    s32 unk_390;            /* 0x390 */
    s32 unk_394;            /* 0x394 */
    u8  pad_398[0x10];
    u8  unk_3a8;            /* 0x3a8 */
#ifdef __cplusplus
    /* methods */
    int Behavior();
    int CleanupResources();
    int InitResources();
    int Render();
    void OnPendingDestroy();
#endif
};

#endif
