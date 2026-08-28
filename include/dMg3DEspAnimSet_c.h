#ifndef DMG3DESPANIMSET_C_H
#define DMG3DESPANIMSET_C_H

#include "MaterialChanger.h"
#include "ModelAnim.h"

/* The source spelling is inferred from the sole owning minigame. The object
 * boundary and member order are compiler-proven: its paired helpers construct
 * three ModelAnim objects followed by three MaterialChanger objects, and tear
 * them down in reverse order. */
struct dMg3DEspAnimSet_c {
    dMg3DEspAnimSet_c();
    ~dMg3DEspAnimSet_c();

    ModelAnim mModels[3];                 /* 0x000 */
    MaterialChanger mMaterialChangers[3]; /* 0x12c */
};

typedef char dMg3DEspAnimSet_c_size_must_be_0x168[
    sizeof(dMg3DEspAnimSet_c) == 0x168 ? 1 : -1];

#endif
