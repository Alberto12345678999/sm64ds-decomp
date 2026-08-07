/* AUTO-GENERATED from matched-function evidence by tools/gen_header.py
 * class Moneybag: 5 matched functions, 19 evidenced fields.
 * Offsets/widths are observed, not guessed. Gaps are explicit padding.
 * Field NAMES are placeholders - renaming cannot change codegen. */
#ifndef MONEYBAG_H
#define MONEYBAG_H
#include "types.h"
#include "ModelAnim.h"
#include "Model.h"
#include "ShadowModel.h"
#include "MovingCylinderClsn.h"
#include "WithMeshClsn.h"

struct Moneybag {
    u8  pad_000[0x5c];
    s32 mPosX;            /* 0x05c */
    s32 mPosY;            /* 0x060 */
    s32 mPosZ;            /* 0x064 */
    u8  pad_068[0x18];
    s32 mScaleX;            /* 0x080 */
    s32 mScaleY;            /* 0x084 */
    s32 mScaleZ;            /* 0x088 */
    u8  pad_08c[0x10];
    s32 unk_09c;            /* 0x09c */
    s32 unk_0a0;            /* 0x0a0 */
    u8  pad_0a4[0xc];
    s32 unk_0b0;            /* 0x0b0 */
    u8  pad_0b4[0x20];
    /* ModelAnim member, named by the class's own destructor calling
       ModelAnim's D1 at +0x0d4 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8MoneybagD0Ev.c] */
    ModelAnim mModelAnim;            /* 0x0d4 */
    /* Model member, named by the class's own destructor calling
       Model's D1 at +0x138 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8MoneybagD0Ev.c] */
    Model mModel;            /* 0x138 */
    /* ShadowModel member, named by the class's own destructor calling
       ShadowModel's D1 at +0x188 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8MoneybagD0Ev.c] */
    ShadowModel mShadowModel;            /* 0x188 */
    /* MovingCylinderClsn member, named by the class's own destructor calling
       MovingCylinderClsn's D1 at +0x1b0 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8MoneybagD0Ev.c] */
    MovingCylinderClsn mMovingCylinderClsn;            /* 0x1b0 */
    /* WithMeshClsn member, named by the class's own destructor calling
       WithMeshClsn's D1 at +0x1e4 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN8MoneybagD0Ev.c] */
    WithMeshClsn mWithMeshClsn;            /* 0x1e4 */
    u8  unk_3a0;            /* 0x3a0 */
    u8  pad_3a1[0x2f];
    s32 unk_3d0;            /* 0x3d0 */
    s32 unk_3d4;            /* 0x3d4 */
    s32 unk_3d8;            /* 0x3d8 */
    u8  pad_3dc[0x14];
    u8  unk_3f0;            /* 0x3f0 */
#ifdef __cplusplus
    /* methods */
    int Behavior();
    int InitResources();
    int Render();
#endif
};

#endif
