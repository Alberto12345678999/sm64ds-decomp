//cpp
#include "dBgCh_SphCrr.h"

struct dBgCh_Actr
{
    char pad[0x20];
    void Unk_0203589c();
};

void dBgCh_Actr::Unk_0203589c()
{
    ((dBgCh_SphCrr*)((char*)this + 0x20))->func_02037b5c();
}
