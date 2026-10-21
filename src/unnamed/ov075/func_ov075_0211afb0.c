// @symbol func_ov075_0211afb0
/* recovered: draws the VS/wireless entry-menu grid mesh, the sub-object
 * dEntObj_c keeps at +0xe80 (d_ent_obj.cpp passes that address to the init
 * func_ov075_0211b458, which installs this function in its step table).
 *
 * Concatenates the object's own matrix (mMtx) with the pooled camera
 * matrix at data_0209b3ec and pushes the result as both the position and the
 * directional matrix, sets a full-white diffuse/ambient and specular/emission
 * pair, then hands the material state to func_ov075_0211a948. The mesh is a
 * (mGridDim[0] - 1) x mGridDim[1] grid of triangle strips over the 0x18-byte
 * vertex array mVertices: each inner iteration emits vertex (i, j) and
 * vertex (i + 1, j), converting each 1.19.12 coordinate to the VTX_16 format
 * with (v << 9) >> 16 and packing x and y into one command word.
 *
 * Two spellings in the vertex emission are load-bearing for the register
 * colouring of the second emission (notes/mwccarm-codegen.md 6ct): the z
 * coordinate is loaded straight into `sz` and shifted in place, and x << 9 is
 * parked in `cols`, the inner loop's bound, which the loop reloads from
 * mGridDim[1] before its next use. Both keep the shift out of the register of
 * the value it consumes, which is where the ROM's compiler puts it.
 */
#include "types.h"

extern void MulMat4x3Mat4x3(const void *m1, const void *m0, void *mF);
extern void func_020553a4(void *m);
extern void func_ov075_0211a948(void *self);
extern int data_0209b3ec;

/* One grid vertex, in func_ov075_0211abb0.c's EntryMeshVertex view with
 * its names. func_ov075_0211b260 lays the grid out and
 * func_ov075_0211abb0 packs the normals. */
typedef struct EntryMeshVertex {
    int x, y, z; /* 0x00 -- 1.19.12, sent here as VTX_16 */
    int dist;    /* 0x0c -- func_ov075_0211af0c: distance from the ripple centre at 0x74 */
    unsigned int normal;   /* 0x10 -- sent to G3_NORMAL (0x4000484) */
    unsigned int texCoord; /* 0x14 -- sent to G3_TEXCOORD (0x4000488) */
} EntryMeshVertex;

typedef char EntryMeshVertex_size_must_be_0x18[sizeof(EntryMeshVertex) == 0x18 ? 1 : -1];

/* The mesh fields this file reads. func_ov075_0211b458 sets both grid
 * dimensions to 0x14, sizes the vertex count at 0xa4 as their product and
 * allocates mVertices to match; func_ov075_0211b3b8 frees it. The grid is
 * square, and this file and func_ov075_0211abb0 both use mGridDim[1] as the
 * row stride, so the two bytes are not split into named axes. */
typedef struct EntryMesh {
    u8 pad_00[0x14];
    int mMtx[12]; /* 0x14 -- model matrix, concatenated with the camera */
    u8 pad_44[0x3c];
    EntryMeshVertex *mVertices; /* 0x80 -- 0x18-byte vertices, mGridDim[0] * mGridDim[1] */
    u8 pad_84[0x22];
    u8 mGridDim[2]; /* 0xa6 */
} EntryMesh;

void func_ov075_0211afb0(char *self)
{
    EntryMesh *mesh = (EntryMesh *)self;
    int z0;
    int z1;
    int tmp[13];
    int i;
    int j;
    int cols;
    EntryMeshVertex *p0;
    EntryMeshVertex *p1;
    int vx;
    int vy;
    int sx;
    int sz;

    *(int *)0x4000444 = 0;
    MulMat4x3Mat4x3(mesh->mMtx, &data_0209b3ec, tmp);
    *(int *)0x4000440 = 2;
    func_020553a4(tmp);
    *(int *)0x4000440 = 1;
    func_020553a4(tmp);
    *(int *)0x40004c8 = 0xe0000000;
    *(int *)0x40004cc = 0xc0007fff;
    func_ov075_0211a948(self);

    *(int *)0x400046c = 0x10000;
    *(int *)0x400046c = 0x10000;
    *(int *)0x400046c = 0x10000;

    z0 = 0;
    z1 = 0;
    i = 0;
    if ((int)(mesh->mGridDim[0] - 1) > 0) {
        do {
            j = z0;
            *(int *)0x4000500 = 2;
            cols = mesh->mGridDim[1];
            if (cols > 0) {
                do {
                    p0 = &mesh->mVertices[i + j * cols];
                    p1 = &mesh->mVertices[i + 1 + j * cols];
                    *(int *)0x4000488 = p0->texCoord;
                    j = j + 1;
                    *(int *)0x4000484 = p0->normal;
                    vx = p0->x;
                    sz = p0->z;
                    cols = vx << 9;
                    sx = cols >> 16;
                    sz = (sz << 9) >> 16;
                    vy = p0->y;
                    *(int *)0x400048c = (u16)sx | ((u16)((vy << 9) >> 16) << 16);
                    *(int *)0x400048c = (u16)sz;
                    *(int *)0x4000488 = p1->texCoord;
                    *(int *)0x4000484 = p1->normal;
                    vx = p1->x;
                    sz = p1->z;
                    cols = vx << 9;
                    sx = cols >> 16;
                    sz = (sz << 9) >> 16;
                    vy = p1->y;
                    *(int *)0x400048c = (u16)sx | ((u16)((vy << 9) >> 16) << 16);
                    *(int *)0x400048c = (u16)sz;
                    cols = mesh->mGridDim[1];
                } while (j < cols);
            }
            i = i + 1;
            *(int *)0x4000504 = z1;
        } while (i < (int)(mesh->mGridDim[0] - 1));
    }
    *(int *)0x4000448 = 1;
}
