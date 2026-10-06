//cpp
#include "dBgCh_SphCrr.h"

struct dBgCh_Actr
{
    char pad[0x20];
    int GetWallResult() const;
};

int dBgCh_Actr::GetWallResult() const
{
    return (int)((dBgCh_SphCrr*)((const char*)this + 0x20))->GetWallResult();
}
