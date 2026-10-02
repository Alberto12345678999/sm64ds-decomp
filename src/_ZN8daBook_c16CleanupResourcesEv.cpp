//cpp
// @symbol _ZN8daBook_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method */
#include "daBook_c.h"
#include "SharedFilePtr.h"
extern "C" {
void UnloadBlueCoinModel(void *);
extern int data_ov020_02114aa0;
extern int data_ov020_02114ab8;
extern int data_ov020_02114aa8;
extern int data_ov020_02114ab0;
}

int daBook_c::CleanupResources()
{
  ((SharedFilePtr *)(&data_ov020_02114aa0))->Release();
  ((SharedFilePtr *)(&data_ov020_02114ab8))->Release();
  ((SharedFilePtr *)(&data_ov020_02114aa8))->Release();
  ((SharedFilePtr *)(&data_ov020_02114ab0))->Release();
  UnloadBlueCoinModel(((void *)this));
  return 1;
}
