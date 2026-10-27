//cpp
#include "types.h"
#include "dBgCh.h"
#include "dCamera_c.h"
#include "Player.h"

extern "C" {

/* func_0200897c @ 0x0200897c, size 0x5c, ARM.
 * dCamera_c-cluster helper taking (dCamera_c *self, void *arg).
 * arg is a dBgCh query. Always runs dBgCh::StopIgnoringVanishSurfaces on it.
 * Then, if the camera's target (mTargetPlayer @0x110) has actorID 0xbf
 * (PLAYER) AND Player::mIsVanish (0x6fb) is set, runs
 * dBgCh::StartIgnoringVanishSurfaces. Finally always runs func_02035468(arg).
 *
 * Codegen note: the (actorID == 0xbf) test is held in an enum-typed boolean.
 * Under -O4 -enum int this materializes the comparison as a full 32-bit 0/1
 * value (cmp; moveq #1; movne #0; cmp #0; beq) instead of folding it into a
 * single branch -- that is what the ROM does. A plain `int` bool folds to a
 * bare `bne`; a `u8` bool masks with `ands #0xff`; only the (int-width) enum
 * bool gives the exact `cmp r0, #0`.
 */
enum Bool { FALSE, TRUE };

extern void func_02035468(void *arg);

void func_0200897c(dCamera_c *self, void *arg) {
    Player *owner;
    enum Bool isType;
    ((dBgCh *)arg)->StopIgnoringVanishSurfaces();
    owner = (Player *)self->mTargetPlayer;
    isType = (enum Bool)(owner->actorID == 0xbf);
    if (isType && owner->mIsVanish != 0) {
        ((dBgCh *)arg)->StartIgnoringVanishSurfaces();
    }
    func_02035468(arg);
}
}
