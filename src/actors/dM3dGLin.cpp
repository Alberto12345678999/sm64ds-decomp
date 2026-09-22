//cpp
/* Recovered translation unit -- ov002/dM3dGLin, the line segment primitive.
 *
 * .text span 0x020fea84..0x020feabc, 2 functions, ROM ordinals 0..1, exactly
 * the contiguous linker run build/tu_map.json places here. Both are assembled
 * below and config/tu_manifest.d/ov002/dM3dGLin.json names every one, so the
 * run has no hole and the 2 one-function files under src/ that used to own
 * these bytes are deleted by this change.
 *
 * IDENTITY IS THE CARTRIDGE'S. The ROM's RTTI names _ZTS8dM3dGLin at
 * 0x02099284 (arm9) and lists it as a BASE of dBgCh_Lin at offset 0x38. The
 * class is non-polymorphic -- no vptr in any body -- so this TU drags in no
 * vtable and no RTTI passengers.
 *
 * FUNCTION ORDER IS THE REVERSE OF THE ROM'S. mwccarm 2004/b56 emits one .text
 * section per function in the reverse of source order, so the HIGHEST-address
 * ROM function (_ZN8dM3dGLinD2Ev, 0x020feab8) is written FIRST and the lowest
 * (_ZN8dM3dGLin3SetERK7Vector3S2_, 0x020fea84) LAST. Do not reorder. The
 * verifier reports both sections in the expected ROM-ascending order with no
 * destructor-order exception.
 *
 * THE DESTRUCTOR IS ONE DEFINITION AND ONE RETAINED SECTION. A single
 * `dM3dGLin::~dM3dGLin()` emits D2 and D1; the ROM keeps only the trivial
 * base-subobject D2 (`bx lr`), so the manifest licenses the homeless D1 as
 * deadstrip compiler-only output.
 *
 * KEY-FUNCTION SIDE EFFECT: none. Non-polymorphic classes own no vtable, and
 * the manifest claims no data or BSS range.
 *
 * The 2 legacy one-function sources this folds are named by the manifest's
 * `legacy_source` fields (history); they are not repeated here.
 */

/* Includes: union of the legacy files', first-seen in ROM-ascending
 * processing order. NOT verified for header ordering constraints (e.g. a
 * common.h-before-X rule) -- watch for new compile errors after this. */
#include "dM3dGLin.h"

/* -------------------------------------------------------------------------- */
/* ROM ordinal 1 -- _ZN8dM3dGLinD2Ev, 0x020feab8, size 0x4 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8dM3dGLinD2Ev
/* recovered: the out-of-line base-subobject destructor retained by the ROM */
dM3dGLin::~dM3dGLin()
{
}

/* -------------------------------------------------------------------------- */
/* ROM ordinal 0 -- _ZN8dM3dGLin3SetERK7Vector3S2_, 0x020fea84, size 0x34 */
/* -------------------------------------------------------------------------- */
// @symbol _ZN8dM3dGLin3SetERK7Vector3S2_
/* recovered: real C++ method
 *
 * A line is exactly its two endpoints. The explicit component copies preserve
 * the ROM's interleaved load/store sequence while stating the geometry through
 * the class's proven Vector3 members.
 */
void dM3dGLin::Set(const Vector3 &start_, const Vector3 &end_)
{
    start.x = start_.x;
    start.y = start_.y;
    start.z = start_.z;
    end.x = end_.x;
    end.y = end_.y;
    end.z = end_.z;
}
