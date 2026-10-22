//cpp
#include "dScEntry_c.h"
#include "types.h"
#include "PlayerInput.h"

extern dScEntry_c::StepSet data_ov075_0211d810;

extern "C" {

extern int func_0203da9c(void);
extern int func_02020168(void);
extern void func_02020304(void);
extern void func_020200e0(void);
extern void func_02012790(int id);
extern int func_0203d9b4(void);
extern void func_02020124(void);
extern void func_02020334(void);
extern void func_02020768(char *thiz);
extern u8 data_0209fc5c[];
extern u8 data_020a0e58[];
extern int data_0208ee44;
extern u16 data_020a0e5a[];
extern u8 data_0209b2f0[];

// 6e: keep pointer-induction un-reduced
#pragma opt_strength_reduction off
// 6e: EBB-local CSE
#pragma opt_common_subs off
void func_ov075_0211867c(char *self)
{
    int id;
    int acc;
    int i;
    int zero;
    int one;
    int bit;
    u8 *p;
    dScEntry_c *scene = reinterpret_cast<dScEntry_c *>(self);

    id = func_0203da9c();
    if (func_02020168() != 0) {
        func_02020304();
        func_020200e0();
        scene->ChangeStepsAfterDelay(&data_ov075_0211d810, 5);
        func_02012790(0x124);
    } else {
        if (func_0203d9b4() != 0) {
            /* mStepWork[3]: set once the mStepDelay countdown has run out
               and func_02020334 has been sent; this step reads it back. */
            if (scene->mStepWork[3] == 0) {
                acc = 0;
                p = data_0209fc5c;
                i = acc;
                zero = acc;
                one = 1;
                do {
                    bit = *p;
                    if (bit != 0) {
                        acc |= *(u16 *)(data_020a0e58 + (i << 2) + 2) & 0xc;
                        if (gTouchHeld[i << 2] != 0 && (gTouchHeld + (i << 2))[1] != 0)
                            bit = one;
                        else
                            bit = zero;
                        acc |= bit;
                    }
                    i = i + 1;
                    p = p + 1;
                } while (i < 4);
                scene->mStepDelay -= data_0208ee44;
                if (scene->mStepDelay <= 0 || (scene->mStepDelay < 0x21c && acc != 0)) {
                    func_02020334();
                    scene->mStepWork[3] = 1;
                }
            } else {
                if (scene->ArePlayersReady() != 0)
                    func_02020124();
            }
        } else if (scene->mStepWork[3] == 0) {
            scene->mStepDelay -= data_0208ee44;
            if (scene->mStepDelay < 0x1e0) {
                func_02020334();
                scene->mStepWork[3] = 1;
            }
        }
        if ((data_020a0e5a[func_0203da9c() * 2] & ~0xc) != 0)
            func_02012790(0xe);
    }

    func_02020768((char *)&scene->mOamAnimations[0]);
    func_02020768((char *)&scene->mOamAnimations[1]);
    func_02020768((char *)&scene->mOamAnimations[2]);
    p = data_0209b2f0 + id;
    if (*p == 0)
        func_02020768((char *)&scene->mOamAnimations[3]);
    if (scene->mOamAnimations[0].enabled == 0) {
        if (scene->mOamAnimations[1].enabled == 0) {
            scene->mOamAnimations[0].affine = 0;
            scene->mOamAnimations[1].enabled = 1;
            scene->mOamAnimations[1].affine = 1;
            if (*p == 0) {
                scene->mOamAnimations[2].enabled = 1;
                scene->mOamAnimations[2].affine = 1;
                scene->mOamAnimations[3].enabled = 1;
                scene->mOamAnimations[3].affine = 1;
            }
        }
    }
}
}
