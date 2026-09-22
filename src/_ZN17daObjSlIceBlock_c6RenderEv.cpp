//cpp
#include "dBgActor_c.h"
// @symbol _ZN17daObjSlIceBlock_c6RenderEv
/* recovered: named members + shared header, real C++ method */
#include "daObjSlIceBlock_c.h"
struct VObj {
  virtual void f0();
  virtual void f1();
  virtual void f2();
  virtual void f3();
  virtual void f4();
  virtual void m5(int);
};
extern "C" {
}

int daObjSlIceBlock_c::Render()
{
  int x = actorID==0x5d;
  if(x){
    ((dBgActor_c *)(((char*)this)))->UpdateModelPosAndRotY();
    ((dBgActor_c *)(((char*)this)))->UpdateClsnPosAndRot();
    ((VObj*)((char*)&mModel))->m5(0);
  }
  return 1;
}
