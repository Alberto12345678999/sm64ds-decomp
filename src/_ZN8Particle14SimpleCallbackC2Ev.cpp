//cpp
// @symbol _ZN8Particle14SimpleCallbackC2Ev
/* recovered: named members + shared header, declarations from a shared header */
#include "decl_common.h"
/* recovered: named members + shared header */
#include "Particle.h"
extern void *_ZTVN5dPa_c7level_c10callback_cE;
extern "C" void _ZN8Particle14SimpleCallbackC2Ev(struct Particle *self) {
    *(void **)((char *)self) = &_ZTVN5dPa_c7level_c10callback_cE;
    *(void **)((char *)self) = &_ZTVN5dPa_c7level_c16simpleCallback_cE;
    *(short *)((char *)&self->unk_004) = 0;
}
