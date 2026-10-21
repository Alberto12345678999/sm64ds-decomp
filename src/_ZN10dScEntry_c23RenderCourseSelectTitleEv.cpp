//cpp
#include "dScEntry_c.h"
#include "OamAttr.h"

// local extern: the Fix12-by-value overload retains its measured scalar ABI bridge.
extern "C" void _ZN3OAM6RenderEbP7OamAttriiii5Fix12IiES3_ii(int sub, struct OamAttr *data, s32 x,
                                                            s32 y, s32 palette, s32 priority,
                                                            s32 scaleX, s32 scaleY, s32 rotation,
                                                            s32 mode);

extern struct OamAttr data_ov075_0211cba4[];

void dScEntry_c::RenderCourseSelectTitle() {
    _ZN3OAM6RenderEbP7OamAttriiii5Fix12IiES3_ii(0, data_ov075_0211cba4, 0x80, 0x20, -1, -1, 0x1000,
                                                0x1000, 0, -1);
}
