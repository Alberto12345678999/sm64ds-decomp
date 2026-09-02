//cpp
// @symbol _ZN15daObjWc_Obj04_c6RenderEv
/* recovered: named members + shared header, real C++ method */
#include "daObjWc_Obj04_c.h"
struct Sub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(int); };

int daObjWc_Obj04_c::Render()
{
  if (mVisible != 0) {
    Sub *s = (Sub*)((char *)&mModel2);
    s->v5(0);
  }
  return 1;
}
