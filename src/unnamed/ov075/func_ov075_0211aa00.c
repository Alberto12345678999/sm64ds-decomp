// @symbol func_ov075_0211aa00
/* recovered: shared common types */
#include "common.h"
extern void Matrix4x3_FromTranslation(void* m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationY(void* m, short angY);
extern void InvMat4x3(void* d, void* s);

extern struct Matrix4x3 data_020a0e68;

/* The entry-menu grid mesh, in func_ov075_0211b458.cpp's EntryMesh view
 * with its names; only the fields this file uses. mMtx is the matrix
 * func_ov075_0211afb0 concatenates with the camera; mInvMtx is its
 * inverse, which nothing in this overlay reads back (medium confidence). */
typedef struct EntryMesh {
    s32 mPos[3]; /* 0x00 */
    s16 mAngleX; /* 0x0c */
    s16 mAngleY; /* 0x0e */
    s16 mAngleZ; /* 0x10 */
    u8 pad_12[2];
    struct Matrix4x3 mMtx;    /* 0x14 */
    struct Matrix4x3 mInvMtx; /* 0x44 */
} EntryMesh;

typedef char EntryMesh_size_must_be_0x74[sizeof(EntryMesh) == 0x74 ? 1 : -1];

void func_ov075_0211aa00(char* r4){
  EntryMesh *mesh = (EntryMesh *)r4;
  Matrix4x3_FromTranslation(&data_020a0e68,
    (mesh->mPos[0] - 0xfa000) >> 3,
    (mesh->mPos[1] - 0xfa000) >> 3,
    mesh->mPos[2] >> 3);
  Matrix4x3_ApplyInPlaceToRotationY(&data_020a0e68, mesh->mAngleY);
  mesh->mMtx = data_020a0e68;
  InvMat4x3(&data_020a0e68, &data_020a0e68);
  mesh->mInvMtx = data_020a0e68;
}
