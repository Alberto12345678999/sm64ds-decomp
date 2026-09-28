//cpp
// @symbol _ZN9dEntObj_c6RenderEv
/* recovered: named members + shared header, real C++ method */
#include "dEntObj_c.h"
extern "C" {
void func_ov075_02114be4(void* p);
void func_ov075_0211b3d8(void* p);
}

namespace Particle {
void RenderAll();
}

int dEntObj_c::Render()
{
    mModel.Render(0);
    ShadowModel::RenderAll();
    mParticles.Update();
    int i = 0;
    UnknownVsPlayer* player = mPlayers;
    do {
        func_ov075_02114be4(player);
        i++;
        player++;
    } while (i < 4);
    if (mAnimActive) {
        mModelAnim.Render(0);
    }
    func_ov075_0211b3d8((char*)&unk_e80);
    Particle::RenderAll();
    return 1;
}
