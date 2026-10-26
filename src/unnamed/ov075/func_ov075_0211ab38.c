#include "private/ov075_entry_mesh.h"
/* recovered: shared common types */
#include "common.h"

typedef struct {
    int x, y, z;
} Vec3;

extern void SubVec3(Vec3 *a, Vec3 *b, Vec3 *out);
extern void CrossVec3(Vec3 *a, Vec3 *b, Vec3 *out);
extern void NormalizeVec3(Vec3 *a, Vec3 *out);
extern void Vec3_Sub(struct Vector3 *out, struct Vector3 *a, struct Vector3 *b);
extern void Vec3_Asr(struct Vector3 *d, struct Vector3 *s, int sh);
extern void func_ov075_0211af84(char *self, int a, int b);

void func_ov075_0211abb0(char *self) {
    Vec3 ej;
    Vec3 ei;
    Vec3 n;
    EntryMesh *mesh = (EntryMesh *)self;
    EntryMeshVertex *p;
    int i;
    int j;
    int mask = 0x3ff;

    p = mesh->mVertices;

    for (i = 0; i < mesh->mGridDim[1]; i++) {
        for (j = 0; j < mesh->mGridDim[0]; j++) {
            int *q;
            int z = 0;
            q = (int *)&ej;
            q[0] = z;
            q[1] = z;
            q[2] = z;
            q = (int *)&ei;
            q[0] = z;
            q[1] = z;
            q[2] = z;
            q = (int *)&n;
            q[0] = z;
            q[1] = z;
            q[2] = z;

            if (j == 0)
                SubVec3((Vec3 *)p, (Vec3 *)(p + 1), &ej);
            else if (j == mesh->mGridDim[0] - 1)
                SubVec3((Vec3 *)(p - 1), (Vec3 *)p, &ej);
            else
                SubVec3((Vec3 *)(p - 1), (Vec3 *)(p + 1), &ej);

            if (i == 0)
                SubVec3((Vec3 *)p, (Vec3 *)(p + mesh->mGridDim[1]), &ei);
            else if (i == mesh->mGridDim[1] - 1)
                SubVec3((Vec3 *)(p - mesh->mGridDim[1]), (Vec3 *)p, &ei);
            else
                SubVec3((Vec3 *)(p - mesh->mGridDim[1]), (Vec3 *)(p + mesh->mGridDim[1]), &ei);

            CrossVec3(&ej, &ei, &n);
            n.z >>= 1;
            NormalizeVec3(&n, &n);
            p->normal = (n.x >> 3 & mask) | ((n.y >> 3 & mask) << 10) | ((n.z >> 3 & mask) << 20);
            p++;
        }
    }
}

// @symbol func_ov075_0211ab38
void func_ov075_0211ab38(char *c, struct Vector3 *arg2) {
    struct Vector3 a;
    struct Vector3 r;
    struct Vector3 out;
    a.x = 0;
    a.y = 0x15e000;
    a.z = -0x320000;
    Vec3_Sub(&out, &a, arg2);
    Vec3_Asr(&r, &out, 3);
    r.x = r.x + 0xfa000;
    r.y = r.y + 0xfa000;
    func_ov075_0211af84(c, r.x, r.y);
}
