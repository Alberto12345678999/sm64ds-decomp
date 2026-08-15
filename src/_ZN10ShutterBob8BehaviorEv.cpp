//cpp
// @symbol _ZN10ShutterBob8BehaviorEv
/* recovered: named members + shared header, real C++ method
 *
 * The local `class Platform { void UpdateClsnPosAndRot(); };` shadow this file
 * used to carry is gone: ShutterBob now really derives from Platform through
 * daObjSwdoor_c, so the call is an ordinary inherited one. It still emits a
 * direct `bl` because Platform::UpdateClsnPosAndRot is non-virtual in the real
 * header, exactly as the shadow declared it -- the shadow's shape was right.
 */
#include "decl_common.h"
#include "ShutterBob.h"

int ShutterBob::Behavior()
{
int r4 = func_ov002_020bac18();
UpdateClsnPosAndRot();
return r4;
}
