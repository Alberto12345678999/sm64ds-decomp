//cpp
// @symbol _ZN10daMcFlag_c8BehaviorEv
#include "daMcFlag_c.h"

extern "C" {
extern void Matrix4x3_FromRotationY(void* m, short angle);
}

int daMcFlag_c::Behavior()
{
    mModelAnim.Advance();
    Matrix4x3_FromRotationY(&mModelAnim.mat4x3, mAngleY);
    mModelAnim.mat4x3.t.x = mPosX >> 3;
    mModelAnim.mat4x3.t.y = mPosY >> 3;
    mModelAnim.mat4x3.t.z = mPosZ >> 3;
    return 1;
}
