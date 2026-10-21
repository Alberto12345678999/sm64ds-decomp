#include "private/ov075_entry_mesh.h"

typedef struct { int x, y, z; } Vec3;

extern void SubVec3(Vec3* a, Vec3* b, Vec3* out);
extern void CrossVec3(Vec3* a, Vec3* b, Vec3* out);
extern void NormalizeVec3(Vec3* a, Vec3* out);

void func_ov075_0211abb0(char* self)
{
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
            q = (int*)&ej; q[0] = z; q[1] = z; q[2] = z;
            q = (int*)&ei; q[0] = z; q[1] = z; q[2] = z;
            q = (int*)&n;  q[0] = z; q[1] = z; q[2] = z;

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
