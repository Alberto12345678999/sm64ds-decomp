//cpp
// @symbol _ZN19FloatingFloorLllBig13InitResourcesEv
/* recovered: named members + shared header, real C++ method, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header, real C++ method */
#include "FloatingFloorLllBig.h"
typedef short s16;
extern "C" {
extern void* _ZN5Model8LoadFileER13SharedFilePtr(void*);
extern int _ZN9ModelBase7SetFileEP8BMD_Fileii(void*, void*, int, int);
extern int _ZN8Platform21UpdateModelPosAndRotYEv(void*);
extern int _ZN8Platform19UpdateClsnPosAndRotEv(void*);
extern void* _ZN12MeshCollider8LoadFileER13SharedFilePtr(void*);
extern int _ZN18MovingMeshCollider7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(void*, void*, void*, int, short, void*);
extern int func_020393d4(void*, void*);
extern int _ZN16MeshColliderBase21UpdatePosWithVelocityERS_P5ActorR10ClsnResultR7Vector3P10Vector3_16S8_(void);
}

int FloatingFloorLllBig::InitResources()
{
  void* mdl;
  void* kcl;
  mdl = _ZN5Model8LoadFileER13SharedFilePtr(data_ov022_02114620);
  _ZN9ModelBase7SetFileEP8BMD_Fileii(&mModel, mdl, 1, -1);
  _ZN8Platform21UpdateModelPosAndRotYEv(((char*)this));
  _ZN8Platform19UpdateClsnPosAndRotEv(((char*)this));
  kcl = _ZN12MeshCollider8LoadFileER13SharedFilePtr(data_ov022_02114618);
  _ZN18MovingMeshCollider7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(&mMeshCollider, kcl, &mClsnMat, 0x1000, mAngleY, data_ov064_0211ba6c);
  func_020393d4(&mMeshCollider, &_ZN16MeshColliderBase21UpdatePosWithVelocityERS_P5ActorR10ClsnResultR7Vector3P10Vector3_16S8_);
  /* A FULL WORD at 0x320, where Platform spells those bytes as two s16.
     Platform owns 0x31e..0x323 -- BowserFireSeaArena derives directly from it
     and starts its own Model at 0x324 -- but how the six bytes divide is
     contested: this class, BlueCoinSwitch and TtcRotatingGear all observed a
     word here, while BowserFireSeaArena observed halfwords. Writing it through
     the cast reproduces the ROM without asserting either division. */
  *(s32 *)&unk_320 = mPosY;
  unk_324 = mAngleX;
  return 1;
}
