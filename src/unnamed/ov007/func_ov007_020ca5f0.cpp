//cpp
#include "types.h"
#include "nitro/fx/fx.h"
#include "cstd.h"
#include "Ov007Mesh.h"
#include "Ov007Texture.h"

extern "C" {

extern void func_ov007_020c1448(Ov007Texture *self, u32 texGen, u32 repeat, u32 flip, u32 color0);
extern void func_ov007_020c1404(Ov007Texture *tex);
extern void func_ov007_020caeac(Vector3 *vtx, Vector3_16 *nrm, s32 *tu, s32 *tv, s32 w, s32 h,
                                s32 u0, s32 v0, s32 du, s32 dv, s32 su, s32 sv, s32 shift);
extern void func_ov007_020ca86c(Vector3 *vtx, Vector3_16 *nrm, s32 w, s32 h, s32 shift);

/* Draws the mesh (data_ov007_02104bd4[0]) with one of its materials
 * ([1] or [2]): sets the material's light colours, texture and polygon
 * attributes, translates by pos and scales z by scaleZ, then emits the
 * grid. With smooth set it is drawn textured with the per-point normals
 * (func_ov007_020caeac), otherwise flat with the face normals clamped to
 * 0xfff (func_ov007_020ca86c). */
void func_ov007_020ca5f0(Ov007Mesh *mesh, Ov007MeshMaterial *mat, int *pos, int scaleZ,
                         int smooth) {
    Ov007Texture *r7 = mat->texture;
    Ov007Grid *pdim = mesh->grid;
    int d0 = pdim->columns - 1;
    int d1 = pdim->rows - 1;
    int tw = 0;
    int th = 0;
    *((volatile u32 *)0x40004c0) = (((u32)mat->diffuse) | (((u32)mat->ambient) << 16)) | 0x8000;
    *((volatile u32 *)0x40004c4) = 0;
    if (r7 != 0) {
        tw = 8 << r7->sizeS;
        th = 8 << r7->sizeT;
    }
    func_ov007_020c1448(r7, 1, mat->texRepeat, 0, mat->texColor0);
    func_ov007_020c1404(r7);
    *((volatile u32 *)0x40004a4) =
        ((0x8c1 | (mat->polygonMode << 4)) | (mat->polygonId << 24)) | (mat->alpha << 16);
    *((volatile u32 *)0x4000444) = 0;
    {
        int t2 = pos[2];
        int t1 = pos[1];
        int t0 = pos[0];
        *((volatile u32 *)0x4000470) = t0;
        *((volatile u32 *)0x4000470) = t1;
        *((volatile u32 *)0x4000470) = t2;
    }
    *((volatile u32 *)0x400046c) = 0x1000;
    *((volatile u32 *)0x400046c) = 0x1000;
    *((volatile u32 *)0x400046c) = scaleZ;
    *((volatile u32 *)0x4000444) = 0;
    *((volatile u32 *)0x400046c) = 0x40000;
    *((volatile u32 *)0x400046c) = 0x40000;
    *((volatile u32 *)0x400046c) = 0x40000;
    if (smooth != 0) {
        int q1 = cstd::div(tw * mat->tilesS, d0);
        int q2 = cstd::div(th * mat->tilesT, d1);
        int fx1 = FX_MUL(mesh->cellWidth, mat->warpS);
        int fx2 = FX_MUL(mesh->cellHeight, mat->warpT);
        func_ov007_020caeac(mesh->verts, mesh->vertexNormals, mesh->texOffsetS, mesh->texOffsetT,
                            d0, d1, mat->texS, mat->texT, q1, q2, fx1, fx2,
                            6);
    } else {
        int n = (d1 * d0) << 1;
        if (n > 0) {
            int i = 0;
            int off = 0;
            tw = n;
            do {
                s16 *p;
                p = (s16 *)((char *)mesh->faceNormals + off);
                if ((*p) > 0xfff) {
                    *p = 0xfff;
                }
                p = (s16 *)((char *)mesh->faceNormals + off);
                if (p[1] > 0xfff) {
                    p[1] = 0xfff;
                }
                p = (s16 *)((char *)mesh->faceNormals + off);
                if (p[2] > 0xfff) {
                    p[2] = 0xfff;
                }
                off += 6;
                i++;
            } while (i < tw);
        }
        func_ov007_020ca86c(mesh->verts, mesh->faceNormals, d0, d1, 6);
    }
    *((volatile u32 *)0x4000448) = 2;
}
}
