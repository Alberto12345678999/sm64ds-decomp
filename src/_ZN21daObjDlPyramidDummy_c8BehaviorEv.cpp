//cpp
// @symbol _ZN21daObjDlPyramidDummy_c8BehaviorEv

#include "daObjDlPyramidDummy_c.h"
#include "daObjDlPyramid_c.h"

s32 daObjDlPyramidDummy_c::Behavior()
{
    if (mCylinder.otherOwner != 0) {
        if (mPyramidTopID == 0) {
            MarkForDestruction();
            return 1;
        }

        daObjDlPyramid_c *top = (daObjDlPyramid_c *)dActor_c::FindWithID(mPyramidTopID);
        if (top != 0)
            ++top->mNumTagsTriggered;

        MarkForDestruction();
        return 1;
    }

    mCylinder.Clear();
    mCylinder.Update();
    return 1;
}
