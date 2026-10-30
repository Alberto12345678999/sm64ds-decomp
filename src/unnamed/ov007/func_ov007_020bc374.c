#include "Ov007Model.h"

extern void func_ov007_020bc3dc(Ov007Model *m, int i, int startFrame);

/* Starts bone animation i at startFrame: when one is already playing,
 * snapshots its player into blendAnim and cross-fades out of it over
 * fadeFrames frames. */
void func_ov007_020bc374(Ov007Model *m, int i, int startFrame, int fadeFrames) {
    Ov007AnimPlayer *src = m->boneAnim;
    if (src->anim != -1) {
        *m->blendAnim = *src;
        m->blendFrames = (s16)fadeFrames;
        m->blendFrameCount = m->blendFrames;
    }
    func_ov007_020bc3dc(m, i, startFrame);
}
