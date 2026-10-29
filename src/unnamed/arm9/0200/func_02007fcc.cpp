//cpp
#include "math/Approach.h"

extern "C" {

extern int ReadUnalignedSignedInt(unsigned char *p);

int func_02007fcc(void *self, const void *src)
{
    int v1 = ReadUnalignedSignedInt((unsigned char *)src);
    int v2 = ReadUnalignedSignedInt((unsigned char *)src + 4);
    /* Camera word 0x170 stays raw: states read it as a height
       (func_020080b0) and as a speed (func_020071e0), so it has no one role. */
    ApproachLinear(*(int *)((char *)self + 0x170), v1, v2);
    return 1;
}
}
