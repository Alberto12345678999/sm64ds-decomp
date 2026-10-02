//cpp
// @symbol _ZN8daBook_c13OnYoshiTryEatEv
#include "daBook_c.h"
/* recovered: renamed to Class_Method */
s32 daBook_c::OnYoshiTryEat() {
    char* c = (char*)this;
  unsigned int b = *(unsigned short*)(c+0xc)==0x147; return b ? 2 : 0;
}
