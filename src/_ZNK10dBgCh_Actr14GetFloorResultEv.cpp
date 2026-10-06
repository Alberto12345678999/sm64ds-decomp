//cpp
#include "dBgCh_SphCrr.h"

struct dBgCh_Actr
{
    char pad[0x20];
    int GetFloorResult() const;
};

int dBgCh_Actr::GetFloorResult() const
{
    return (int)((dBgCh_SphCrr*)((const char*)this + 0x20))->GetFloorResult();
}
