//cpp
#include "dScEntry_c.h"
#include "dEntObj_c.h"

extern "C" {
int func_0203d974();
int func_0203da9c();
u8 func_02020168();
void func_02020304();
void func_020200e0();
void func_ov075_0211a148(char *, int, int);
void func_02020334();
int func_0203d9b4();
// The existing readiness call passes the scene even though the helper does not
// use it. Removing that argument drops the retail r0 setup instruction.
int func_ov075_02116d40(char *);
void func_02020124();
extern int data_ov075_0211d780[];
extern int data_0208ee44;
}

// @symbol _ZN10dScEntry_c23UpdatePlayerSelectIntroEv
void dScEntry_c::UpdatePlayerSelectIntro() {
    if (func_0203d974()) {
        if (!mPlayerSelectReady) {
            mEntObj->func_ov075_02115134();
            if (mEntObj->func_ov075_02115098(func_0203da9c()))
                mPlayerSelectReady = 1;
        }
        if (mPlayerSelectReady)
            mStepPhase = 1;
    }

    if (func_02020168()) {
        func_02020304();
        func_020200e0();
        func_ov075_0211a148(reinterpret_cast<char *>(this),
                            reinterpret_cast<int>(data_ov075_0211d780), 5);
        return;
    }

    if (mStepDelay > 0) {
        mStepDelay -= data_0208ee44;
        return;
    }
    if (!mStepPhase)
        return;
    func_02020334();
    if (!func_0203d9b4())
        return;
    if (!func_ov075_02116d40(reinterpret_cast<char *>(this)))
        return;
    func_02020124();
}
