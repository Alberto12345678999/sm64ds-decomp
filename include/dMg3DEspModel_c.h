#ifndef DMG3DESPMODEL_C_H
#define DMG3DESPMODEL_C_H

#include "ModelAnim.h"
#include "TextureSequence.h"
#include "dMg3DEspAnimSet_c.h"

/* The source spelling is inferred from its sole owner, dScMg3DEsp_c. The
 * 0x21c-byte extent and member lifetime are fixed by its exact constructor/
 * destructor pair. */
struct dMg3DEspModel_c {
    dMg3DEspModel_c();
    ~dMg3DEspModel_c();

    s32 unk_000;                      /* 0x000 */
    s32 unk_004;                      /* 0x004 */
    s32 unk_008;                      /* 0x008 */
    ModelAnim mModelAnim;             /* 0x00c */
    TextureSequence mTextureSequence; /* 0x070 */
    dMg3DEspAnimSet_c mAnimSet;       /* 0x084 */
    u8 pad_1ec[0x18];                 /* 0x1ec */
    u32 unk_204;                      /* 0x204 */
    s32 unk_208;                      /* 0x208 */
    s32 unk_20c;                      /* 0x20c */
    u8 mState[0x08];                  /* 0x210 -- pointer-to-member state */
    s16 mTextureFrame;                /* 0x218 */
    u8 mPolygonID;                    /* 0x21a */
    u8 pad_21b;                       /* 0x21b */
};

typedef char dMg3DEspModel_c_size_must_be_0x21c[
    sizeof(dMg3DEspModel_c) == 0x21c ? 1 : -1];

#endif
