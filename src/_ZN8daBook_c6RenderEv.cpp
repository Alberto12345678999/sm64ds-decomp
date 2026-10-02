//cpp
// @symbol _ZN8daBook_c6RenderEv

#include "daBook_c.h"

int daBook_c::Render()
{
    bool isHidden = mFlags & 0x40000;
    if (isHidden != 0)
        return 1;

    if (unk_450 != 0)
        mModelAnim.Render((Vector3 *)&mScaleX);
    else
        mModel.Render((Vector3 *)&mScaleX);

    return 1;
}
