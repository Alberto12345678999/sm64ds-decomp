// @symbol _ZN5UnagiD1Ev
/* recovered: named members + shared header, declarations from a shared header */
#include "decl_BlendModelAnim.h"
#include "decl_WithMeshClsn.h"
#include "decl_common.h"
/* recovered: named members + shared header */
#include "Unagi.h"
extern int __destroy_arr(void*, int, int, void*);
extern void _ZN25MovingCylinderClsnWithPosD1Ev(void*);
extern int _ZN5EnemyD2Ev(int*);
extern void _ZN7Vector3D1Ev(void);

int _ZN5UnagiD1Ev(struct Unagi *self) {
    *(void**)((void*)self) = _ZTV5Unagi;
    __destroy_arr((char*)((void*)self) + 0x448, 7, 0xc, (void*)_ZN7Vector3D1Ev);
    _ZN14BlendModelAnimD1Ev((char*)&self->mBlendModelAnim);
    _ZN12WithMeshClsnD1Ev((char*)&self->mWithMeshClsn);
    _ZN25MovingCylinderClsnWithPosD1Ev((char*)&self->mMovingCylinderClsnWithPos2);
    _ZN25MovingCylinderClsnWithPosD1Ev((char*)&self->mMovingCylinderClsnWithPos1);
    _ZN5EnemyD2Ev((int*)((void*)self));
    return (int)((void*)self);
}
