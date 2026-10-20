#include "types.h"
#include "nitro/fx/fx.h"

/* File-local view of Particle::System (include/Particle__System.h is C++):
   the direction and the two axes perpendicular to it. */
typedef struct {
    u8 pad_000[0x3c];
    Vector3s direction; /* 0x3c */
    u8 pad_042[0x1a];
    Vector3s basisU; /* 0x5c */
    Vector3s basisV; /* 0x62 */
} ParticleSystemView;

extern Vector3s data_02099fc4;
extern void func_02053380(void *a, Vector3s *b);

void func_0204cebc(void *c)
{
    ParticleSystemView *sys = (ParticleSystemView *)c;
    Vector3s vecA;
    Vector3s vecB;

    vecA = data_02099fc4;
    func_02053380(&sys->direction, &vecB);

    if (vecA.x == vecB.x && vecA.y == vecB.y && vecA.z == vecB.z) {
        vecA.x = 0x1000;
        vecA.y = 0;
        vecA.z = 0;
    }

    sys->basisU.x = (s16)(FX_MUL(vecB.y, vecA.z) - FX_MUL(vecB.z, vecA.y));
    sys->basisU.y = (s16)(FX_MUL(vecB.z, vecA.x) - FX_MUL(vecB.x, vecA.z));
    sys->basisU.z = (s16)(FX_MUL(vecB.x, vecA.y) - FX_MUL(vecB.y, vecA.x));

    sys->basisV.x = (s16)(FX_MUL(vecB.y, sys->basisU.z) - FX_MUL(vecB.z, sys->basisU.y));
    sys->basisV.y = (s16)(FX_MUL(vecB.z, sys->basisU.x) - FX_MUL(vecB.x, sys->basisU.z));
    sys->basisV.z = (s16)(FX_MUL(vecB.x, sys->basisU.y) - FX_MUL(vecB.y, sys->basisU.x));
}
