//cpp
// @symbol _ZN5UnagiD0Ev
/* recovered: named members + shared header, declarations from a shared header */
#include "decl_BlendModelAnim.h"
#include "decl_WithMeshClsn.h"
#include "decl_common.h"
/* recovered: named members + shared header */
#include "Unagi.h"
extern "C" {
extern int __destroy_arr(void*,int,int,void*);
extern void _ZN25MovingCylinderClsnWithPosD1Ev(void*);
extern int _ZN5EnemyD2Ev(int*);
extern void _ZN7Vector3D1Ev(void);
extern void* data_020a0eac[];
void* _ZN5UnagiD0Ev(struct Unagi *self) {
  *(int**)((char*)self) = _ZTV5Unagi;
  __destroy_arr(((char*)self)+0x448, 7, 0xc, (void*)_ZN7Vector3D1Ev);
  _ZN14BlendModelAnimD1Ev((char*)&self->mBlendModelAnim);
  _ZN12WithMeshClsnD1Ev((char*)&self->mWithMeshClsn);
  _ZN25MovingCylinderClsnWithPosD1Ev((char*)&self->mMovingCylinderClsnWithPos2);
  _ZN25MovingCylinderClsnWithPosD1Ev((char*)&self->mMovingCylinderClsnWithPos1);
  _ZN5EnemyD2Ev((int*)((char*)self));
  _ZN6Memory10DeallocateEPvP4Heap(((char*)self), data_020a0eac[0]);
  return ((char*)self);
}
}
