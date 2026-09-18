//cpp
// @symbol _ZN5Bully13InitResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "Bully.h"

int Bully::InitResources()
{
    mBigBullyID = 0;
    mFileTable = (int)&data_ov064_0211b834;
    InitResourcesCommon();
}
