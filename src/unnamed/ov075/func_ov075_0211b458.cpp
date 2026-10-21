//cpp
// @symbol func_ov075_0211b458
/* recovered: shared common types */
#include "common.h"
#include "SharedFilePtr.h"
#include "private/ov075_entry_mesh.h"

extern "C" {
extern void* _ZN6Memory13operator_new2Ej(unsigned int sz);
extern void* func_0201787c(void* sfp);
extern void func_ov075_0211aa94(void* a, void* b);
extern void func_ov075_0211aa00(char* r4);
extern char data_ov075_0211d980;
}
extern EntryMeshHandler data_ov075_0211d994;

extern "C" int func_ov075_0211b458(char* c, int* src, int a2) {
    EntryMesh *mesh = (EntryMesh *)c;

    mesh->mGridDim[0] = 0x14;
    mesh->mGridDim[1] = 0x14;
    mesh->mNumVertices = mesh->mGridDim[0] * mesh->mGridDim[1];
    mesh->mVertices = (EntryMeshVertex *)_ZN6Memory13operator_new2Ej(mesh->mNumVertices * sizeof(EntryMeshVertex));
    func_ov075_0211aa94(c, func_0201787c(&data_ov075_0211d980));
    ((SharedFilePtr *)(&data_ov075_0211d980))->Release();
    mesh->mState = &data_ov075_0211d994;
    (mesh->*(*mesh->mState))();
    mesh->mPos[0] = src[0];
    mesh->mPos[1] = src[1];
    mesh->mPos[2] = src[2];
    mesh->mAngleX = 0;
    mesh->mAngleY = a2;
    mesh->mAngleZ = 0;
    func_ov075_0211aa00(c);
    return 1;
}
