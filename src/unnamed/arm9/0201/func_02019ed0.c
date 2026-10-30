#include "types.h"
extern u8 data_0209d4e4;
extern void func_0205f77c(int a, int b, int c);
/* Sleep with the lid closed. data_0209d4e4 is up while it sleeps (the
   pull-out thread func_02019f64 reads it). func_0205f77c(0xc, 0, 0) has
   PM_GoSleepMode's argument list, with the lid-open (4) and card (8)
   wake triggers. The lid check func_02019ac4 calls it. */
void func_02019ed0(void){
  data_0209d4e4 = 1;
  func_0205f77c(0xc, 0, 0);
  data_0209d4e4 = 0;
}
