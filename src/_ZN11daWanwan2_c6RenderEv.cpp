//cpp
// @symbol _ZN11daWanwan2_c6RenderEv
/* recovered: real C++ method over the typed model members */
#include "daWanwan2_c.h"

int daWanwan2_c::Render()
{
    mModelAnim.Render((Vector3 *)&mScaleX);
    for (int i = 0; i < 5; i++)
        mModels[i].Render(0);
    return 1;
}
