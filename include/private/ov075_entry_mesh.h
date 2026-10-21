#ifndef OV075_ENTRY_MESH_H
#define OV075_ENTRY_MESH_H

#include "common.h"

/* The entry-menu grid mesh, the 0xa8-byte sub-object dEntObj_c keeps at
 * +0xe80 (d_ent_obj.cpp passes that address to the init
 * func_ov075_0211b458). The cartridge gives it no class name; these are
 * the names the ov075 mesh functions already used. A square grid of
 * mGridDim[0] x mGridDim[1] vertices, drawn as triangle strips and
 * rippled outward from a touched point. */

/* One grid vertex. func_ov075_0211b260 lays the grid out,
 * func_ov075_0211abb0 packs the normals and func_ov075_0211afb0 sends
 * each vertex to the geometry engine. */
typedef struct EntryMeshVertex {
    s32 x, y, z; /* 0x00 -- 1.19.12, sent as VTX_16 */
    s32 dist;    /* 0x0c -- func_ov075_0211af0c: distance from mRippleCenter */
    /* 0x10: the packed 10-bit x/y/z normal func_ov075_0211abb0 builds;
       func_ov075_0211afb0 sends it to G3_NORMAL (0x4000484). */
    u32 normal;
    u32 texCoord; /* 0x14 -- sent to G3_TEXCOORD (0x4000488) */
} EntryMeshVertex;

/* The mesh's material block, filled by func_ov075_0211aa94 and pushed to
 * the geometry engine by func_ov075_0211a948: the same five words, in the
 * same order, as daPicGate_c's record (include/private/Ov080Mat.h), with
 * that header's names. */
typedef struct EntryMeshMaterial {
    u32 texAddr; /* 0x00 */
    u32 pltAddr; /* 0x04 */
    u32 difAmb;  /* 0x08 */
    u32 speEmi;  /* 0x0c */
    u32 param;   /* 0x10 -- TEXIMAGE_PARAM format, size and pltt0 bits */
} EntryMeshMaterial;

#ifdef __cplusplus
struct EntryMesh;
/* One handler of the {init, behavior, render} row mState points at. */
typedef void (EntryMesh::*EntryMeshHandler)();
#endif

typedef struct EntryMesh {
    s32 mPos[3]; /* 0x00 -- func_ov075_0211aa00 translates mMtx by it */
    s16 mAngleX; /* 0x0c -- only zeroed, by func_ov075_0211b458 (medium confidence) */
    s16 mAngleY; /* 0x0e -- func_ov075_0211aa00 rotates mMtx by it */
    s16 mAngleZ; /* 0x10 -- only zeroed, by func_ov075_0211b458 (medium confidence) */
    u8 pad_12[2];
    /* 0x14: the model matrix func_ov075_0211aa00 builds and
       func_ov075_0211afb0 concatenates with the camera. */
    struct Matrix4x3 mMtx;
    /* 0x44: mMtx's inverse, which func_ov075_0211aa00 stores; nothing in
       this overlay reads it back (medium confidence). */
    struct Matrix4x3 mInvMtx;
    /* 0x74: the touched point func_ov075_0211af84 starts a ripple at
       (func_ov075_0211ab38 maps the touch into grid space). */
    s32 mRippleCenter[3];
    EntryMeshVertex *mVertices; /* 0x80 -- mNumVertices of them */
    /* 0x84: a {init, behavior, render} row of handlers. Init runs in
       func_ov075_0211b458; dEntObj_c::Behavior runs +0x8
       (func_ov075_0211b418) and dEntObj_c::Render +0x10
       (func_ov075_0211b3d8). */
#ifdef __cplusplus
    EntryMeshHandler *mState;
#else
    void *mState;
#endif
    EntryMeshMaterial mMaterial; /* 0x88 */
    u8 pad_9c[6];
    /* 0xa2: frames left in the ripple, from 100. func_ov075_0211b1cc
       counts it down; func_ov075_0211addc displaces a vertex only while
       it is nonzero, within a radius that grows with 100 - mRippleTimer. */
    u16 mRippleTimer;
    u16 mNumVertices; /* 0xa4 -- mGridDim[0] * mGridDim[1] */
    /* 0xa6: the grid is square (func_ov075_0211b458 sets both to 0x14) and
       func_ov075_0211afb0 and func_ov075_0211abb0 both use mGridDim[1] as
       the row stride, so the two bytes are not split into named axes. */
    u8 mGridDim[2];
} EntryMesh;

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char EntryMeshVertex_size_must_be_0x18[sizeof(EntryMeshVertex) == 0x18 ? 1 : -1];
typedef char EntryMeshMaterial_size_must_be_0x14[sizeof(EntryMeshMaterial) == 0x14 ? 1 : -1];
typedef char EntryMesh_size_must_be_0xa8[sizeof(EntryMesh) == 0xa8 ? 1 : -1];
typedef char EntryMesh_mMtx_at_0x14[(int)&((EntryMesh *)0)->mMtx == 0x14 ? 1 : -1];
typedef char EntryMesh_mVertices_at_0x80[(int)&((EntryMesh *)0)->mVertices == 0x80 ? 1 : -1];
typedef char EntryMesh_mRippleTimer_at_0xa2[(int)&((EntryMesh *)0)->mRippleTimer == 0xa2 ? 1 : -1];
#endif

#endif
