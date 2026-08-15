// @symbol _ZN8Particle10SysTrackerC1Ev
/* recovered: named members + shared header, declarations from a shared header */
#include "decl_Particle.h"
#include "decl_common.h"
/* recovered: named members + shared header */
#include "Particle.h"

extern char _ZTVN5dPa_c7level_c10callback_cE[];
extern void *data_0209ee74;

void *_ZN8Particle10SysTrackerC1Ev(struct Particle *self) {
    func_02021c90((char *)&self->unk_008);
    _ZN8Particle14SimpleCallbackC2Ev((char *)&self->mParticle1);
    _ZN8Particle14SimpleCallbackC2Ev((char *)&self->mParticle2);
    func_020226a4((char *)&self->unk_76c);
    *(void **)((char *)&self->unk_76c) = _ZTVN5dPa_c7level_c16splashCallback_cE;
    func_020226a4((char *)&self->unk_778);
    *(void **)((char *)&self->unk_778) = _ZTVN5dPa_c7level_c16splashCallback_cE;
    func_020226a4((char *)&self->unk_784);
    *(void **)((char *)&self->unk_784) = _ZTVN5dPa_c7level_c16bubbleCallback_cE;
    func_020226a4((char *)&self->unk_790);
    *(void **)((char *)&self->unk_790) = _ZTVN5dPa_c7level_c24fitWaterSimpleCallback_cE;
    _ZN8Particle14SimpleCallbackC2Ev((char *)&self->mParticle3);
    _ZN8Particle14SimpleCallbackC2Ev((char *)&self->mParticle4);
    func_020225fc((char *)&self->unk_7b4);
    func_020225fc((char *)&self->unk_7c4);
    func_020225fc((char *)&self->unk_7d4);
    func_020225fc((char *)&self->unk_7e4);
    *(volatile void **)((char *)&self->unk_7f0) = _ZTVN5dPa_c7level_c10callback_cE;
    *(volatile void **)((char *)&self->unk_7f0) = _ZTVN5dPa_c7level_c20checkWaterCallback_cE;
    *(volatile void **)((char *)&self->unk_7f4) = _ZTVN5dPa_c7level_c10callback_cE;
    *(volatile void **)((char *)&self->unk_7f4) = _ZTVN5dPa_c7level_c26checkWaterRippleCallback_cE;
    *(volatile void **)((char *)&self->unk_7f8) = _ZTVN5dPa_c7level_c10callback_cE;
    *(volatile void **)((char *)&self->unk_7f8) = _ZTVN5dPa_c7level_c18fitWaterCallback_cE;
    self->unk_7fc = 0x3000;
    *(volatile void **)((char *)&self->unk_800) = _ZTVN5dPa_c7level_c10callback_cE;
    *(volatile void **)((char *)&self->unk_800) = _ZTVN5dPa_c7level_c18fitWaterCallback_cE;
    self->unk_804 = 0x3000;
    func_020226a4((char *)&self->unk_808);
    *(void **)((char *)&self->unk_808) = _ZTVN5dPa_c7level_c20checkYoganCallback_cE;
    *(volatile void **)((char *)&self->unk_810) = _ZTVN5dPa_c7level_c10callback_cE;
    *(volatile void **)((char *)&self->unk_810) = _ZTVN5dPa_c7level_c14clipCallback_cE;
    self->unk_814 = 1;
    *(volatile void **)((char *)&self->unk_818) = _ZTVN5dPa_c7level_c10callback_cE;
    *(volatile void **)((char *)&self->unk_818) = _ZTVN5dPa_c7level_c23cleanParticleCallback_cE;
    data_0209ee74 = ((char *)self);
    self->unk_004 = 0;
    self->unk_750 = 0;
    self->unk_75c = 0;
    self->unk_768 = 0;
    self->unk_774 = 0;
    self->unk_780 = 0;
    self->unk_78c = 0;
    self->unk_798 = 0;
    self->unk_7a4 = 0;
    self->unk_7b0 = 0;
    self->unk_7c0 = 0;
    self->unk_804 = 0x4b000;
    return ((char *)self);
}
