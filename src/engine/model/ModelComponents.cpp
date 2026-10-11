//cpp
/* ModelComponents -- the bone/skeleton half of a loaded model (transforms at
 * +0x0c rebuilt from the BMD bone list), arm9 0x02044dc4..0x0204547c,
 * 10 functions: UpdateVertsUsingBones, UpdateBones, func_020453c0 + 7 helpers.
 * The file takes the class name already used in the tree (include/ModelBase.h),
 * per Juan 2026-10-11.
 *
 * SCOPE: func_02044b30.c below is not complete, so Render (0x020443c8) and the
 * helpers under it stay out. func_020453c0 is the bone-tree walk UpdateBones
 * forwards to. Next above is func_0204547c.c, a Model leftover, and it stays out.
 *
 * mwccarm emits .text in reverse source order here, so definitions run from
 * the highest address (func_020453c0) down to the lowest (func_02044dc4).
 * Descending order defines every in-span callee before its callers, so only
 * out-of-span callees need extern declarations.
 *
 * The two struct Node layouts the shards carried (func_02044f74's full
 * f0..f2c record, func_02045074's f0..fc prefix) are one shared definition:
 * the short form is an exact prefix of the long one and func_02045074 only
 * touches f0/f8/fa/fc, so every accessed offset is identical. The
 * func_02044efc Matrix4x3 typedef is dropped for include/ModelBase.h's; both
 * bodies use it opaquely through pointers. No helper is promoted: none has
 * ROM method evidence, so all seven stay extern "C" under their existing
 * names. func_0204531c's UpdateVertsUsingBones call is spelled as the member
 * it is (ModelBase.h); the mangled extern the shard used would be a new
 * local redeclaration of a header member.
 */
#include "ModelBase.h"
#include "types.h"

struct Sub {
    unsigned char *bytes;
    unsigned short *halfs;
    char pad8[4];
    char *blk;
};
struct Self {
    struct Inner *p0;
    char pad[8];
    char *m;
};
struct Inner {
    char pad[0x34];
    struct Sub *sub;
};

typedef struct {
    char pad0[4];
    u32 count;         /* +4 */
    u32 param8;        /* +8 */
    char padC[0x24];
    u32 unk30;         /* +0x30 */
    u32* matData;      /* +0x34 */
} Obj;

struct Node {
    s16 f0; s16 f2; s16 f4; s16 f6;
    s16 f8; s16 fa; s16 fc; s16 fe;
    int f10, f14, f18;
    u16 f1c, f1e, f20; s16 f22;
    int f24, f28, f2c;
};

struct Elem {
    int f0, f4, f8;
    int fc, f10, f14;
    u16 f18, f1a, f1c, f1e;
    int f20, f24, f28, f2c, f30;
};

struct G {
    int f0, f4;
    struct Elem* f8;
    int fc;
};

extern "C" {
void Matrix4x3_LoadIdentity(Matrix4x3 *mat);
int InvMat4x3(int *a, int *b);
void _ZN4CP1514FlushDataCacheEv(void);
void func_02048234(int *out, int sa, int sb, int sc, int ax, int ay, int az, int tx, int ty, int tz);
void MulMat4x3Mat4x3(const int *A, const int *B, int *dst);
void func_02047218(void *a, void *b, void *out, int c);
void func_02047910(int *m0, int *m1, int *dst, int t);
void func_0204547c(int *a, int b, int c, void *elem);
extern s16 data_02082214[];
}

// @symbol func_020453c0
/* Bone-tree walk at 0x020453c0. UpdateBones forwards here. Recurses on the
 * node's child and sibling slots and calls func_0204547c, which stays out. */
extern "C" {
void func_020453c0(int *a, short *node, int *p2, int p3)
{
    int idx = node[0];
    char *elem = (char*)a[2] + idx * 0x34;
    int f2c = *(int*)(elem + 0x2c);
    int *r6 = p2;
    int r5 = p3;
    if (f2c != 0) {
        r6 = (int*)f2c;
        r5 = *(unsigned short*)(elem + 0x30);
    }
    int mla = idx * 0x24 + r6[5];
    unsigned short *dst;
    func_0204547c(r6, mla, r5, elem);
    dst = (unsigned short*)(int)(elem + 0x18);
    *dst = (unsigned short)(*dst | *(unsigned short*)(elem + node[4] * 0x34 + 0x18));
    if (node[5] != 0)
        func_020453c0(a, (short*)((char*)node + (node[5] << 6)), r6, r5);
    if (node[6] != 0)
        func_020453c0(a, (short*)((char*)node + (node[6] << 6)), r6, r5);
}
}

// @symbol _ZN15ModelComponents11UpdateBonesEP8BCA_Filei
/* ModelComponents::UpdateBones(BCA_File*, int) at 0x02045394 -- apply a bone
 * animation frame. Forwards to func_020453c0 with this, the BMD bone table
 * (modelFile->bones), the BCA file, and the frame index. */
void ModelComponents::UpdateBones(BCA_File *file, int frame)
{
    func_020453c0((int *)this, (short *)modelFile->bones, (int *)file, frame);
}

// @symbol func_0204531c
extern "C" {
void func_0204531c(char *self, int arg)
{
    unsigned int i;
    int a;
    int off;
    int save = *(int *)(self + 0xc);
    a = *(int *)(self + 0x10);

    *(int *)(self + 0xc) = a;
    ((ModelComponents *)self)->UpdateVertsUsingBones();
    *(int *)(self + 0xc) = save;

    i = 0;
    if (i >= *(unsigned int *)(*(int *)self + 4))
        return;

    off = i;
    do {
        func_02047910((int *)(*(int *)(self + 0xc) + off), (int *)a, (int *)(*(int *)(self + 0xc) + off), arg);
        i++;
        off += 0x30;
        a += 0x30;
    } while (i < *(unsigned int *)(*(int *)self + 4));
}
}

// @symbol func_02045178
extern "C" {
void func_02045178(int *out, int ax, int ay, int az, int tx, int ty, int tz) {
    s16 *t = data_02082214;
    int ia = ax >> 4;
    int ib = ay >> 4;
    int ic = az >> 4;
    int a0 = t[ia * 2];
    int a1 = t[ia * 2 + 1];
    int b0 = t[ib * 2];
    int b1 = t[ib * 2 + 1];
    int c0 = t[ic * 2];
    int c1 = t[ic * 2 + 1];
    int p00 = (int)(((s64)a0 * c0) >> 12);
    int p11 = (int)(((s64)a1 * c1) >> 12);
    int p01 = (int)(((s64)a0 * c1) >> 12);
    int p10 = (int)(((s64)a1 * c0) >> 12);

    out[0] = (int)(((s64)b1 * c1) >> 12);
    out[1] = (int)(((s64)b1 * c0) >> 12);
    out[2] = -b0;
    out[3] = (int)(((s64)b0 * p01 + 0x800) >> 12) - p10;
    out[4] = p11 + (int)(((s64)b0 * p00 + 0x800) >> 12);
    out[5] = (int)(((s64)b1 * a0) >> 12);
    out[6] = p00 + (int)(((s64)b0 * p11 + 0x800) >> 12);
    out[7] = (int)(((s64)b0 * p10 + 0x800) >> 12) - p01;
    out[8] = (int)(((s64)b1 * a1) >> 12);
    out[9] = tx;
    out[10] = ty;
    out[11] = tz;
}
}

// @symbol func_02045074
extern "C" {
void func_02045074(struct G *g, struct Node *n)
{
    int m[12];
    int a = n->f0;
    struct Elem *e = (struct Elem *)((char *)g->f8 + a * 0x34);
    if (e->f18 == 0) {
        func_02045178(m,
            e->f1a, e->f1c, e->f1e,
            e->f20, e->f24, e->f28);
    } else {
        func_02048234(m,
            e->fc, e->f10, e->f14,
            e->f1a, e->f1c, e->f1e,
            e->f20, e->f24, e->f28);
    }
    {
        int t = g->fc;
        MulMat4x3Mat4x3(&m[0], (const int *)((a + n->f8) * 0x30 + t), (int *)(a * 0x30 + t));
    }
    if (n->fa != 0) func_02045074(g, (struct Node *)((char *)n + n->fa * 0x40));
    if (n->fc != 0) func_02045074(g, (struct Node *)((char *)n + n->fc * 0x40));
}
}

// @symbol _ZN15ModelComponents21UpdateVertsUsingBonesEv
/* ModelComponents::UpdateVertsUsingBones() at 0x0204504c -- reset the per-bone
 * transform array to identity, then rebuild vertex positions from the BMD
 * bone list via func_02045074. The bones pointer passed to the helper is
 * modelFile->bones (BMD_File @0x08), not the ModelComponents::bones field. */
void ModelComponents::UpdateVertsUsingBones()
{
    Matrix4x3_LoadIdentity(transforms);
    func_02045074((struct G *)this, (struct Node *)modelFile->bones);
}

// @symbol func_02044f74
extern "C" {
void func_02044f74(void *g, struct Node *n)
{
    int m[12];
    int a = n->f0;
    func_02048234(m,
        n->f10, n->f14, n->f18,
        ((unsigned)n->f1c << 20) >> 16,
        ((unsigned)n->f1e << 20) >> 16,
        ((unsigned)n->f20 << 20) >> 16,
        n->f24, n->f28, n->f2c);
    {
        int *base = *(int **)((char *)g + 0x34);
        int t = base[3];
        MulMat4x3Mat4x3(&m[0], (const int *)((a + n->f8) * 0x30 + t), (int *)((s16)a * 0x30 + t));
    }
    if (n->fa != 0) func_02044f74(g, (struct Node *)((char *)n + n->fa * 0x40));
    if (n->fc != 0) func_02044f74(g, (struct Node *)((char *)n + n->fc * 0x40));
}
}

// @symbol func_02044efc
extern "C" {
void func_02044efc(Obj *self) {
    if (!self->unk30) return;
    Matrix4x3 *matrices = (Matrix4x3 *)self->matData[3];
    Matrix4x3_LoadIdentity(matrices);
    func_02044f74((void *)self, (struct Node *)self->param8);
    u32 count = self->count;
    u32 i = 0;
    if (i < count) {
        u32 byteOff = 0;
        do {
            Matrix4x3 *mat = (Matrix4x3 *)((char *)((Matrix4x3 *)self->matData[3]) + byteOff);
            InvMat4x3((int *)mat, (int *)mat);
            count = self->count;
            i++;
            byteOff += 0x30;
        } while (i < count);
    }
    _ZN4CP1514FlushDataCacheEv();
}
}

// @symbol func_02044e50
extern "C" {
void func_02044e50(struct Self *self, int count, int base, int *out)
{
    int i;
    struct Inner *in = self->p0;
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
    out[4] = 0; out[5] = 0; out[6] = 0; out[7] = 0;
    out[8] = 0; out[9] = 0; out[10] = 0; out[11] = 0;
    for (i = 0; i < count; i++) {
        struct Sub *sub = in->sub;
        int idx = base + i;
        unsigned short lh = sub->halfs[idx];
        unsigned char b = sub->bytes[idx];
        func_02047218(self->m + lh * 0x30, sub->blk + lh * 0x30, out, b << 4);
    }
}
}

// @symbol func_02044dc4
extern "C" {
void func_02044dc4(struct Self *self) {
    unsigned int i;
    int r7;
    char *r6;
    r6 = *(char **)self;
    r7 = *(int *)(r6 + 4) * 0x30 + *(int *)((char *)self + 0xc);
    for (i = 0; i < *(unsigned int *)(r6 + 0x30); i++) {
        unsigned short *arr = *(unsigned short **)(*(char **)(r6 + 0x34) + 8);
        func_02044e50(self, arr[2 * i], arr[2 * i + 1], (int *)r7);
        r7 += 0x30;
    }
}
}
