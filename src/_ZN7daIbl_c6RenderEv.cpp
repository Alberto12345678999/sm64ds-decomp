//cpp
// @symbol _ZN7daIbl_c6RenderEv
/* recovered: named members + shared header, real C++ method */
#include "daIbl_c.h"
struct EmbeddedClass {
  virtual void method(void* a);
  virtual void dummy1();
  virtual void dummy2();
  virtual void dummy3();
  virtual void dummy4();
  virtual void virtualMethod(char* a);
};

int daIbl_c::Render()
{
  unsigned char b = mVariant;
  if(b){
    EmbeddedClass* e = (EmbeddedClass*)((char*)&mModel);
    e->virtualMethod((char*)&mDrawScaleX);
  }
  return 1;
}
