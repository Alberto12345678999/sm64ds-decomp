//cpp
#include "SharedFilePtr.h"
extern "C" {
extern int _ZTVN8daDemo_c13simpleModel_cE[];
extern int _ZN7Vector3D1Ev[];
void _ZN5ModelD2Ev(void*);
void __destroy_arr(void*, int, int, void*);
void _ZN6Memory16operator_delete2EPv(void*);
void* func_ov002_020f69a8(char* c){
  void* p;
  *(int*)c = (int)_ZTVN8daDemo_c13simpleModel_cE;
  p = *(void**)(c+0x5c);
  if(p!=0){
    ((SharedFilePtr *)(p))->Release();
  }
  _ZN5ModelD2Ev(c);
  __destroy_arr(c+0x50, 1, 0xc, (void*)_ZN7Vector3D1Ev);
  _ZN6Memory16operator_delete2EPv(c);
  return c;
}
}
