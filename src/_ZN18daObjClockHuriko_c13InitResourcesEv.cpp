//cpp
#include "daObjClockHuriko_c.h"
#include "SharedFilePtr.h"

extern SharedFilePtr data_ov013_02112280;
extern "C" void func_ov013_02111238(daObjClockHuriko_c *pendulum);

s32 daObjClockHuriko_c::InitResources()
{
    void *file = Model::LoadFile(data_ov013_02112280);
    mModel.SetFile((BMD_File *)file, 1, -1);
    func_ov013_02111238(this);
    mAngSpeed = 0x100;
    return 1;
}
