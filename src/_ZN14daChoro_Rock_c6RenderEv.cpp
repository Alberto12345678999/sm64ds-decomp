//cpp
// @symbol _ZN14daChoro_Rock_c6RenderEv
/* recovered: named members + shared header, real C++ method */
#include "daChoro_Rock_c.h"
extern "C" {
struct Base{ virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void m(void*); };
}

s32 daChoro_Rock_c::Render()
{
  Base*b=(Base*)((char*)&(*(Model *)&mModel));
  b->m((char*)&mScaleX);
  return 1;
}
