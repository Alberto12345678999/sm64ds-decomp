//cpp
// @symbol func_ov075_0211b458
/* recovered: shared common types */
#include "common.h"
#include "SharedFilePtr.h"

struct Foo;
typedef void (Foo::*PMF)();
extern "C" {
extern void* _ZN6Memory13operator_new2Ej(unsigned int sz);
extern void* func_0201787c(void* sfp);
extern void func_ov075_0211aa94(void* a, void* b);
extern void func_ov075_0211aa00(char* r4);
extern char data_ov075_0211d980;
}
extern PMF data_ov075_0211d994;

/* The entry-menu grid mesh dEntObj_c keeps at +0xe80, in
 * func_ov075_0211afb0.c's EntryMesh view with its names; only the fields
 * this file sets. mState and mNumVertices follow daPicGate_c, whose
 * picture mesh has the same shape (a State row of init/behavior/render
 * handlers, a u16 vertex count beside the two u8 grid dimensions). */
struct EntryMesh {
    s32 mPos[3];      /* 0x00 -- func_ov075_0211aa00 translates mMtx by it */
    s16 mAngleX;      /* 0x0c -- only zeroed here (medium confidence) */
    s16 mAngleY;      /* 0x0e -- func_ov075_0211aa00 rotates mMtx by it */
    s16 mAngleZ;      /* 0x10 -- only zeroed here (medium confidence) */
    u8 pad_12[0x6e];
    char *mVertices;  /* 0x80 -- 0x18-byte vertices, mNumVertices of them */
    /* 0x84: a {init, behavior, render} row of handlers. Init runs here;
       dEntObj_c::Behavior runs +0x8 (func_ov075_0211b418) and
       dEntObj_c::Render +0x10 (func_ov075_0211b3d8). */
    PMF *mState;
    u8 pad_88[0x1c];
    u16 mNumVertices; /* 0xa4 -- mGridDim[0] * mGridDim[1] */
    u8 mGridDim[2];   /* 0xa6 */
};

typedef char EntryMesh_size_must_be_0xa8[sizeof(EntryMesh) == 0xa8 ? 1 : -1];

extern "C" int func_ov075_0211b458(char* c, int* src, int a2) {
    EntryMesh *mesh = (EntryMesh *)c;

    mesh->mGridDim[0] = 0x14;
    mesh->mGridDim[1] = 0x14;
    mesh->mNumVertices = mesh->mGridDim[0] * mesh->mGridDim[1];
    mesh->mVertices = (char *)_ZN6Memory13operator_new2Ej(mesh->mNumVertices * 0x18);
    func_ov075_0211aa94(c, func_0201787c(&data_ov075_0211d980));
    ((SharedFilePtr *)(&data_ov075_0211d980))->Release();
    mesh->mState = &data_ov075_0211d994;
    (((Foo *)c)->*(*mesh->mState))();
    mesh->mPos[0] = src[0];
    mesh->mPos[1] = src[1];
    mesh->mPos[2] = src[2];
    mesh->mAngleX = 0;
    mesh->mAngleY = a2;
    mesh->mAngleZ = 0;
    func_ov075_0211aa00(c);
    return 1;
}
