//cpp
// @symbol _ZN10daChRoom_c13InitResourcesEv
/* recovered: named members + shared header, real C++ method */
#include "daChRoom_c.h"


int daChRoom_c::InitResources()
{
  mScaleX=(((param1&0xf)+1)*0x64000)>>1;
  mScaleY=(((param1>>4&0xf)+1)*0x64000);
  mAngleY=-mAngleY;
  return 1;
}
