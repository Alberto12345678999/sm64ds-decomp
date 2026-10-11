//cpp
// @symbol _ZN6Player19func_ov002_020d6048Ev
#include "Player.h"
extern "C" {
struct State;
extern State data_ov002_02110064;
extern int _ZN6Player7IsStateERNS_5StateE(void* c, State* st);
}
int Player::func_ov002_020d6048(){
  char* c = (char*)this;
  if(_ZN6Player7IsStateERNS_5StateE(c, &data_ov002_02110064)){
    if(*(unsigned char*)(c+0x6e3)==3) return 1;
  }
  return 0;
}
