//cpp
#include "types.h"
#include "dFader_c.h"

/* The soft reset: holding L+R+START+SELECT (pad bits 0x30c, which
   func_0203bc7c turns into data_020a0e44) asks the running scene to fade out
   and restart. data_0209f1e0 is the pending request, data_0209f1dc keeps a
   held combo from firing again until it is let go, and data_0209f1d8 turns the
   combo off (set by func_02030aa4 for a link session, and by the minigame
   scene when gMgSaveDirty is 1). dScene_c::BeforeBehavior runs the fade out
   with data_0209f1e4 and then destroys the scene. */
extern "C" {

extern unsigned char data_0209f1e0;
extern unsigned char data_0209b2fc;
extern unsigned char gMgSaveDirty;
extern void func_0202fd2c(void);
extern void func_0202ed48(void);
extern void func_02011c8c(void);
extern int GetSoundMode(void);
extern void SetSoundMode(int mode);
extern void func_0203bc50(void);
extern void func_0203bb14(void);
extern void ResetInput(void);
extern unsigned char data_0209f1dc;
extern unsigned char data_0209f1d8;
extern unsigned char data_020a0e44;
/* local extern: decl_common.h spells it void *; it holds the soft reset's
   fader (dScene_c::BeforeBehavior stores &data_0209f5d0, a dFdBrightness_c). */
extern dFader_c *data_0209f1e4;

/* Clear the soft reset request, with data_0209b2fc and gMgSaveDirty, and
   re-apply the current sound mode. dScene_c::BeforeBehavior calls it when
   the request lands on a scene whose actorID is 0; dScDSMT_c::InitResources
   calls it too. */
void func_02023544(void) {
    data_0209f1e0 = 0;
    func_0202fd2c();
    data_0209b2fc = 0;
    gMgSaveDirty = 0;
    func_0202ed48();
    func_02011c8c();
    SetSoundMode(GetSoundMode());
}

/* Once a frame (func_020197b8, after the pads are read): while a reset is
   pending, clear every player's buttons and touch (func_0203bc50,
   func_0203bb14, ResetInput); otherwise raise one on a fresh combo. */
void func_02023498(void) {
    if (data_0209f1e0 != 0) {
        func_0203bc50();
        func_0203bb14();
        ResetInput();
        return;
    }
    if (data_0209f1dc != 0) {
        if (data_020a0e44 == 0)
            data_0209f1dc = 0;
        return;
    }
    if (data_0209f1d8 != 0)
        return;
    if (data_020a0e44 != 0) {
        data_0209f1e0 = 1;
        data_0209f1dc = 1;
    }
}

/* Step the soft reset's fader, if one is running (func_02019390). */
void func_0202345c(void) {
    dFader_c *fader = data_0209f1e4;
    if (!fader)
        return;
    fader->AdvanceFade();
}
}
