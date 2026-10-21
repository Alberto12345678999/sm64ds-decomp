//cpp
#include "dScEntry_c.h"
#include "dEntObj_c.h"
extern "C" {
void func_0203d918();
extern int data_0209fc68;
extern u8 data_0208a0e0;
}
void dScEntry_c::EnterMatchLoading() {
    mEntObj->func_ov075_02114fa8();
    mStepDelay = 240;
    mStepPhase = MATCH_LOAD_RESOURCES;
    mSawLoadSignal = 0;
    if (data_0209fc68 != 0)
        data_0208a0e0 = 4;
    func_0203d918();
}
