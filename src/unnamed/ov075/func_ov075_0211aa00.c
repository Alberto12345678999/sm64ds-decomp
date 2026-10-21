// @symbol func_ov075_0211aa00
/* recovered: shared common types */
#include "common.h"
#include "private/ov075_entry_mesh.h"
extern void Matrix4x3_FromTranslation(void* m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationY(void* m, short angY);
extern void InvMat4x3(void* d, void* s);

extern struct Matrix4x3 data_020a0e68;

void func_ov075_0211aa00(char *r4) {
    EntryMesh *mesh = (EntryMesh *)r4;
    Matrix4x3_FromTranslation(&data_020a0e68, (mesh->mPos[0] - 0xfa000) >> 3,
                              (mesh->mPos[1] - 0xfa000) >> 3, mesh->mPos[2] >> 3);
    Matrix4x3_ApplyInPlaceToRotationY(&data_020a0e68, mesh->mAngleY);
    mesh->mMtx = data_020a0e68;
    InvMat4x3(&data_020a0e68, &data_020a0e68);
    mesh->mInvMtx = data_020a0e68;
}
