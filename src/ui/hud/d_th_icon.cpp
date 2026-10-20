//cpp
/* dThIcon_c -- the polymorphic touch-screen icon base, ov001.
 *
 * RTTI names dThIcon_c. Both virtuals are defined out of line here;
 * constructor and destructor are inline in include/dThIcon_c.h, so this
 * TU anchors the vague-linkage group and emits no C1/C2/D0/D1/D2.
 * The unit spans ov001 .text 0x020ab54c..0x020ab5f8: Render, Behavior,
 * then the icon placement helper func_ov001_020ab5b0.
 *
 * FUNCTION ORDER IS THE REVERSE OF THE ROM'S. mwccarm emits one .text
 * section per function, and with codegen deferred -- the default, which
 * this unit leaves alone -- every body is generated at end of file in
 * the reverse of source order. Behavior before Render puts Render first
 * in the object. No optimisation pragma is needed.
 *
 * deslop
 * Leftover: the field names are coined (see include/dThIcon_c.h); the
 *   cartridge carries none. unk_01c / unk_020 are unused in this TU and
 *   mean something different in each derived icon.
 * Leftover: data_0208ee44 stays the linker name (arm9 frame delta).
 */

#include "dThIcon_c.h"

extern "C" {

extern int data_0208ee44;

}

// @symbol func_ov001_020ab5b0
/* Place an icon: store its touch kind, centre and half extents, clear
 * mPressTimer, mOn and mPenInside, arm it at once when the kind is
 * touchable (the latch Behavior applies), and set the press reload to
 * ten. The highest address in this unit, so first in the file. Callers
 * in ov004/ov006/ov075 pass the icon as a char *, so the entry keeps it. */
extern "C" void func_ov001_020ab5b0(char *p, int kind, short x, short y,
                                    short halfW, short halfH)
{
    dThIcon_c *icon = reinterpret_cast<dThIcon_c *>(p);
    icon->mTouchKind = kind;
    icon->mX = x;
    icon->mY = y;
    icon->mHalfW = halfW;
    icon->mHalfH = halfH;
    icon->mPressTimer = 0;
    icon->mOn = 0;
    icon->mPenInside = 0;
    if (icon->mTouchKind >= 1)
        icon->mReady = 1;
    icon->mPressTime = 10;
}

// @symbol _ZN9dThIcon_c8BehaviorEv
void dThIcon_c::Behavior()
{
    if (mPressTimer <= 0)
        return;

    mPressTimer -= data_0208ee44;
    if (mPressTimer > 0)
        return;

    if (mOn != 0)
        mOn = 0;
    else
        mOn = 1;

    if (mTouchKind >= 1)
        mReady = 1;
}

// @symbol _ZN9dThIcon_c6RenderEv
void dThIcon_c::Render()
{
}
