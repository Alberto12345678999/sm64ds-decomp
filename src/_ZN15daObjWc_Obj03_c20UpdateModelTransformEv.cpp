//cpp
#include "daObjWc_Obj03_c.h"

extern "C" void Matrix4x3_FromRotationY(Matrix4x3 *, int);

void daObjWc_Obj03_c::UpdateModelTransform()
{
    Matrix4x3_FromRotationY(&mModel.mat4x3, mAngleY);
    mModel.mat4x3.t.x = mPosX >> 3;
    mModel.mat4x3.t.y = mPosY >> 3;
    mModel.mat4x3.t.z = mPosZ >> 3;
}
