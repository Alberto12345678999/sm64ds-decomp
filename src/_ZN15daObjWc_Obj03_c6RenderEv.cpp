//cpp
// @symbol _ZN15daObjWc_Obj03_c6RenderEv
#include "daObjWc_Obj03_c.h"

int daObjWc_Obj03_c::Render()
{
    Model *model = &mModel;
    model->Render(0);
    return 1;
}
