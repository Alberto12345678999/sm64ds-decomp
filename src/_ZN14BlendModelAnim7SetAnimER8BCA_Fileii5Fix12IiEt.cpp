//cpp
#include "types.h"
/* BlendModelAnim::SetAnim at 0x020163e0, size=0x9c
 * Fast path (same file): update flags + speed only.
 * Slow path: store file, SetAnimation, then set up blend weight/step
 * (unk64 = current blend, unk68 = per-frame step = 1 / (numBlendFrames+1)).
 */
struct BCA_File {
    u16 unk00;
    u16 numFrames;
};

struct dExtFrameCtrl_c {
    void* vtable;
    s32 numFramesAndFlags;
    s32 currFrame;
    s32 speed;
};

struct BlendModelAnim {
    char pad[0x50];
    dExtFrameCtrl_c anim;      // 0x50
    BCA_File* file;      // 0x60
    s32 blendWeight;     // 0x64
    s32 blendStep;       // 0x68
};

extern "C" {
void _ZN15dExtFrameCtrl_c8SetFlagsEi(dExtFrameCtrl_c* anim, s32 flags);
void _ZN15dExtFrameCtrl_c12SetAnimationEti5Fix12IiEt(dExtFrameCtrl_c* anim, u16 frames, s32 flags, s32 speed, u16 startFrame);
s32 _ZN4cstd4fdivEii(s32 num, s32 den);

void _ZN14BlendModelAnim7SetAnimER8BCA_Fileii5Fix12IiEt(BlendModelAnim* thiz, BCA_File& file, s32 numBlendFrames, s32 flags, s32 speed, u16 startFrame)
{
    if (&file == thiz->file)
    {
        _ZN15dExtFrameCtrl_c8SetFlagsEi(&thiz->anim, flags);
        thiz->anim.speed = speed;
    }
    else
    {
        thiz->file = &file;
        _ZN15dExtFrameCtrl_c12SetAnimationEti5Fix12IiEt(&thiz->anim, file.numFrames, flags, speed, startFrame);
        if (numBlendFrames <= 0)
        {
            thiz->blendWeight = 0x1000;
        }
        else
        {
            thiz->blendWeight = 0;
            thiz->blendStep = _ZN4cstd4fdivEii(0x1000, (numBlendFrames + 1) << 12);
        }
    }
}
}
