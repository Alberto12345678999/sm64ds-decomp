extern void func_ov075_0211af0c(void *self);

/* The entry-menu grid mesh, in func_ov075_0211b458.cpp's EntryMesh view,
 * extended by the ripple this file starts; only the fields it writes.
 * func_ov075_0211ab38 maps a touch to grid coordinates and calls this.
 * func_ov075_0211af0c then stores each vertex's distance from
 * mRippleCenter, func_ov075_0211b1cc counts mRippleTimer down once a
 * frame, and func_ov075_0211addc displaces a vertex only while it is
 * nonzero and only within a radius that grows with 100 - mRippleTimer. */
typedef struct EntryMesh {
    unsigned char pad_00[0x74];
    int mRippleCenter[3]; /* 0x74 */
    unsigned char pad_80[0x22];
    unsigned short mRippleTimer; /* 0xa2 -- frames left, from 100 */
} EntryMesh;

typedef char EntryMesh_size_must_be_0xa4[sizeof(EntryMesh) == 0xa4 ? 1 : -1];

void func_ov075_0211af84(char *self, int a, int b)
{
    EntryMesh *mesh = (EntryMesh *)self;

    mesh->mRippleCenter[0] = a;
    mesh->mRippleCenter[1] = b;
    mesh->mRippleCenter[2] = 0;
    func_ov075_0211af0c(self);
    mesh->mRippleTimer = 100;
}
