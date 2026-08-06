/* AUTO-GENERATED from matched-function evidence by tools/gen_header.py
 * class Stump: 6 matched functions, 8 evidenced fields.
 * Offsets/widths are observed, not guessed. Gaps are explicit padding.
 * Field NAMES are placeholders - renaming cannot change codegen. */
#ifndef STUMP_H
#define STUMP_H
#include "types.h"
#include "MovingCylinderClsn.h"
#include "WithMeshClsn.h"

struct Stump {
    u8  pad_000[0x8];
    s32 unk_008;            /* 0x008 */
    u8  pad_00c[0x94];
    s32 unk_0a0;            /* 0x0a0 */
    u8  pad_0a4[0xc];
    s32 unk_0b0;            /* 0x0b0 */
    u8  pad_0b4[0x5c];
    /* MovingCylinderClsn member, named by the class's own destructor calling
       MovingCylinderClsn's D1 at +0x110 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN5StumpD1Ev.c] */
    MovingCylinderClsn mMovingCylinderClsn;            /* 0x110 */
    /* WithMeshClsn member, named by the class's own destructor calling
       WithMeshClsn's D1 at +0x144 -- a relocation the ROM build
       checks. Was a u8 marker. [_ZN5StumpD1Ev.c] */
    WithMeshClsn mWithMeshClsn;            /* 0x144 */
    u8  mModelAnim;            /* 0x300 */
    u8  pad_301[0x5b];
    s32 unk_35c;            /* 0x35c */
    u8  pad_360[0x14];
    s32 mVariant;            /* 0x374 */
#ifdef __cplusplus
    /* methods */
    int Behavior();
    int CleanupResources();
    int InitResources();
    int Render();
#endif
};

#endif
