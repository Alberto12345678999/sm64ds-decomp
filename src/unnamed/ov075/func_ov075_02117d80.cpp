//cpp
// @symbol func_ov075_02117d80
/* recovered: a dScEntry_c two-icon menu setup. The ENTRY scene (actorID 6)
 * only has func_02034414 draw sub-screen message 0x19; the RESULT scene
 * loads file 0x9802, draws message 0x16 and takes data_ov075_0211d810's
 * render step. The predicate was
 * called IsVsMode, but both scenes are VS scenes; it tests actorID 6, ENTRY
 * (as d_s_entry_methods.cpp's isEntry test reads it), so it is IsEntryScene.
 *
 * Logic first recovered by andrewboudreau as a non-matching body against
 * mwccarm 1.2/sp2p3; byte-matched here at 2004/b56 without changing what it
 * does. Two shapes were load-bearing: the mode test is a static inline
 * predicate in a C++ TU (the ROM materializes the bool, which no measured
 * C-mode spelling reproduced - notes 6c/6bm), and the pair of words copied
 * out of data_ov075_0211d810 is one aggregate copy (that step set's render
 * step into mRenderStep, a pointer-to-member), which keeps both loads ahead
 * of the flag read-modify-write instead of sinking the second one past the
 * first store.
 */
#include "dScEntry_c.h"
#include "types.h"

extern "C" {
extern void func_02034414(unsigned short n);
extern int LoadFile(int handle);
extern void func_ov075_02116030(void *c, int v);
extern void func_ov075_02115e8c(void *c, int a, int b, int d, int e);
}
extern unsigned char data_0209d454;
extern int data_ov075_0211d71c;
extern dScEntry_c::StepSet data_ov075_0211d810;

static inline int IsEntryScene(const dScEntry_c *scene) {
    return scene->actorID == 6;
}

extern "C" void func_ov075_02117d80(char *c)
{
    dScEntry_c *scene = reinterpret_cast<dScEntry_c *>(c);
    int fh;
    int v0, v1;

    data_0209d454 = data_0209d454 & ~1;
    if (IsEntryScene(scene)) {
        func_02034414(0x19);
    } else {
        data_0209d454 = data_0209d454 & ~4;
        fh = LoadFile(0x9802);
        func_ov075_02116030(&data_ov075_0211d71c, fh);
        func_02034414(0x16);
        data_0209d454 = data_0209d454 | 4;
        scene->mRenderStep = data_ov075_0211d810.render;
    }
    data_0209d454 = data_0209d454 | 1;
    scene->mIconCount = 2;
    scene->mSelectedIcon = 1;
    func_ov075_02115e8c(&scene->mIcons[0], 8, 0, 0x50, 0xa8);
    func_ov075_02115e8c(&scene->mIcons[1], 8, 0, 0xb0, 0xa8);
}
