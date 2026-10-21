typedef struct { int x, y, z; } Vec3;

extern void SubVec3(Vec3* a, Vec3* b, Vec3* out);
extern void CrossVec3(Vec3* a, Vec3* b, Vec3* out);
extern void NormalizeVec3(Vec3* a, Vec3* out);

/* The entry-menu grid mesh, in func_ov075_0211afb0.c's EntryMesh view with
 * its names; only the fields this file reads. mGridDim[0] is the length of
 * a run of adjacent vertices and mGridDim[1] the run count and row stride. */
typedef struct EntryMeshVertex {
    int x, y, z; /* 0x00 */
    int dist;    /* 0x0c -- func_ov075_0211af0c: distance from 0x74 */
    /* 0x10: the packed 10-bit x/y/z normal this file builds;
       func_ov075_0211afb0 sends it to G3_NORMAL (0x4000484). */
    unsigned int normal;
    unsigned int texCoord; /* 0x14 -- sent to G3_TEXCOORD (0x4000488) */
} EntryMeshVertex;

typedef struct EntryMesh {
    unsigned char pad_00[0x80];
    EntryMeshVertex *mVertices; /* 0x80 */
    unsigned char pad_84[0x22];
    unsigned char mGridDim[2]; /* 0xa6 */
} EntryMesh;

typedef char EntryMeshVertex_size_must_be_0x18[sizeof(EntryMeshVertex) == 0x18 ? 1 : -1];

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
                SubVec3((Vec3*)p, (Vec3*)(p + 1), &ej);
            else if (j == mesh->mGridDim[0] - 1)
                SubVec3((Vec3*)(p - 1), (Vec3*)p, &ej);
            else
                SubVec3((Vec3*)(p - 1), (Vec3*)(p + 1), &ej);

            if (i == 0)
                SubVec3((Vec3*)p, (Vec3*)(p + mesh->mGridDim[1]), &ei);
            else if (i == mesh->mGridDim[1] - 1)
                SubVec3((Vec3*)(p - mesh->mGridDim[1]), (Vec3*)p, &ei);
            else
                SubVec3((Vec3*)(p - mesh->mGridDim[1]),
                        (Vec3*)(p + mesh->mGridDim[1]), &ei);

            CrossVec3(&ej, &ei, &n);
            n.z >>= 1;
            NormalizeVec3(&n, &n);
            p->normal = (n.x >> 3 & mask)
                | ((n.y >> 3 & mask) << 10)
                | ((n.z >> 3 & mask) << 20);
            p++;
        }
    }
}
