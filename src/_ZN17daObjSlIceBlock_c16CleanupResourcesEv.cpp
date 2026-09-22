//cpp
// @symbol _ZN17daObjSlIceBlock_c16CleanupResourcesEv
/* recovered: named members + shared header, real C++ method */
#include "daObjSlIceBlock_c.h"
#include "SharedFilePtr.h"
#include "dBgW.h"
extern char data_ov027_02113be8[];
extern char data_ov027_02113be0[];

int daObjSlIceBlock_c::CleanupResources()
{
  unsigned char ok = (actorID==0x5d);
  if(ok){ ((dBgW *)((char *)&(*(u8 *)&mMeshCollider)))->Disable(); }
  ((SharedFilePtr *)(data_ov027_02113be8))->Release();
  ((SharedFilePtr *)(data_ov027_02113be0))->Release();
  return 1;
}
