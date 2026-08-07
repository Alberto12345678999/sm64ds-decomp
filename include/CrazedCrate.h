/* AUTO-GENERATED from matched-function evidence by tools/gen_header.py
 * class CrazedCrate: 5 matched functions, 14 evidenced fields.
 * Offsets/widths are observed, not guessed. Gaps are explicit padding.
 * Field NAMES are placeholders - renaming cannot change codegen. */
#ifndef CRAZEDCRATE_H
#define CRAZEDCRATE_H
#include "types.h"
#include "Model.h"
#include "ShadowModel.h"
#include "MovingCylinderClsn.h"

struct CrazedCrate {
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
    /* Model member, named by the class's own destructor calling
       Model's D1 at +0x0d4 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN11CrazedCrateD0Ev.c] */
    Model mModel;            /* 0x0d4 */
    /* ShadowModel member, named by the class's own destructor calling
       ShadowModel's D1 at +0x124 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN11CrazedCrateD0Ev.c] */
    ShadowModel mShadowModel;            /* 0x124 */
    /* MovingCylinderClsn member, named by the class's own destructor calling
       MovingCylinderClsn's D1 at +0x14c -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN11CrazedCrateD0Ev.c] */
    MovingCylinderClsn mMovingCylinderClsn;            /* 0x14c */
    u8  mWithMeshClsn;            /* 0x180 */
    u8  pad_181[0x1f3];
    s32 unk_374;            /* 0x374 */
#ifdef __cplusplus
    /* methods */
    int Behavior();
    int InitResources();
    int Render();
#endif
};

#endif
