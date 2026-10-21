#include "private/ov075_entry_mesh.h"

extern void func_ov075_0211af0c(void *self);

void func_ov075_0211af84(char *self, int a, int b)
{
    EntryMesh *mesh = (EntryMesh *)self;

    mesh->mRippleCenter[0] = a;
    mesh->mRippleCenter[1] = b;
    mesh->mRippleCenter[2] = 0;
    func_ov075_0211af0c(self);
    mesh->mRippleTimer = 100;
}
