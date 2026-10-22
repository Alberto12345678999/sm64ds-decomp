//cpp
#include "dScEntry_c.h"
#include "AsyncJob.h"
extern "C" {
extern int func_0203d8fc(void);
extern int func_0201a1bc(void);
extern void func_0203d930(void);

extern int data_0209fc68;
extern unsigned char EntryCourseLoadStarted;
extern unsigned char data_0209b2e4;
extern int data_0208ee44;
}
void dScEntry_c::UpdateMatchLoading() {
    if (mSawLoadSignal == 0) {
        if (func_0203d8fc() != 0)
            mSawLoadSignal = 1;
    }
    if (mStepPhase == MATCH_LOAD_RESOURCES) {
        if (data_0209fc68 != 0) {
            if (EntryCourseLoadStarted == 0) {
                func_0201a244(&dScEntry_c::LoadCourseResources, data_0209b2e4, 0xf, 0, 0x1000);
                EntryCourseLoadStarted = 1;
            }
            if (EntryCourseLoadStarted != 0 && func_0201a1bc() != 0) {
                mStepPhase = MATCH_LOAD_WAIT_FOR_SIGNAL_CLEAR;
                EntryCourseLoadStarted = 0;
                func_0203d930();
            }
        } else {
            mStepPhase = MATCH_LOAD_READY;
        }
    }
    if (mStepPhase == MATCH_LOAD_WAIT_FOR_SIGNAL_CLEAR && mSawLoadSignal != 0) {
        if (func_0203d8fc() == 0)
            mStepPhase = MATCH_LOAD_READY;
    }
    if (mStepDelay > 0) {
        mStepDelay -= data_0208ee44;
    }
    if (mStepPhase < MATCH_LOAD_READY)
        return;
    if (mStepDelay > 0)
        return;
    StartMatch();
    mBehaviorStep = 0;
}
