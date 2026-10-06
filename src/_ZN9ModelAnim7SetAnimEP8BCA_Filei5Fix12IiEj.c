#include "types.h"
/* ModelAnim::SetAnim at 0x02016748, size=0x5c
 * Sets animation; fast path (same file) updates flags+speed only.
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

struct ModelAnim {
    char pad[0x50];
    struct dExtFrameCtrl_c anim;
    struct BCA_File* file;
};

extern void _ZN15dExtFrameCtrl_c8SetFlagsEi(struct dExtFrameCtrl_c* anim, s32 flags);
extern void _ZN15dExtFrameCtrl_c12SetAnimationEti5Fix12IiEt(struct dExtFrameCtrl_c* anim, u16 frames, s32 flags, s32 speed, u16 startFrame);

void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(struct ModelAnim* thiz, struct BCA_File* animFile, s32 flags, s32 speed, u16 startFrame)
{
    if (animFile == thiz->file)
    {
        _ZN15dExtFrameCtrl_c8SetFlagsEi(&thiz->anim, flags);
        thiz->anim.speed = speed;
    }
    else
    {
        thiz->file = animFile;
        _ZN15dExtFrameCtrl_c12SetAnimationEti5Fix12IiEt(&thiz->anim, animFile->numFrames, flags, speed, startFrame);
    }
}
