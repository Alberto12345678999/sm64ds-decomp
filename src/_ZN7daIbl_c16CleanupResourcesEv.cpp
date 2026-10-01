//cpp
// @symbol _ZN7daIbl_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method */
#include "daIbl_c.h"
#include "SharedFilePtr.h"
extern char data_ov100_02148668;

int daIbl_c::CleanupResources()
{
    char *file = *(char **)((char *)&unk_3a8);

    if (file != 0) {
        (*(unsigned char *)(((int)file + 0x3d2)))--;
    }

    ((SharedFilePtr *)(&data_ov100_02148668))->Release();
    return 1;
}
