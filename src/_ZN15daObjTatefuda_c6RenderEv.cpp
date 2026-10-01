//cpp
// @symbol _ZN15daObjTatefuda_c6RenderEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "daObjTatefuda_c.h"
extern "C" {
}
struct Sub041 {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual void v3(); virtual void v4(); virtual void v5(int);
};

int daObjTatefuda_c::Render()
{
  if (mHidden != 0) return 1;
  void* r = mHoldingPlayer;
  if (r != 0) {
    int b = (mFlags & 0x4000) != 0;
    if (b && *(int*)((char*)r+0xc8) != 0) {
      func_ov002_020bb060(((char*)this));
    }
  }
  Sub041* s = (Sub041*)&mModel;
  s->v5(0);
  return 1;
}
