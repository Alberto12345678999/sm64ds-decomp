//cpp
// @symbol _ZN8dActor_c19DropShadowRadHeightER17dExtShadowModel_cR9Matrix4x35Fix12IiES5_j
/* recovered: named members + shared header, real C++ method */
#include "dActor_c.h"
#include "dExtShadowModel_c.h"

/* dExtShadowModel_c::InitModel is itself wall 6az (its own Fix12<int> params), so
   its DEFINITION is the plain-scalar mangled name below -- calling that
   directly, rather than through the real method, needs no Fix12<int>
   temporary at this call site. See include/dExtShadowModel_c.h. */
extern "C" void _ZN17dExtShadowModel_c9InitModelEP9Matrix4x35Fix12IiES3_S3_j(
    dExtShadowModel_c *self, Matrix4x3 *m, int sx, int sy, int sz, u32 opacity);

/* Stays a mangled free definition: the real signature carries Fix12<int> and
   wall 6az (notes/mwccarm-codegen.md) homes class-typed by-value parameters.
   The declaration in dActor_c.h is the real one and callers may use it. */
extern "C" void _ZN8dActor_c19DropShadowRadHeightER17dExtShadowModel_cR9Matrix4x35Fix12IiES5_j(
    dActor_c *self, dExtShadowModel_c *shadow, Matrix4x3 *matrix,
    int radius, int depth, u8 opacity)
{
    if (self->mFlags & 0x10)
        return;
    _ZN17dExtShadowModel_c9InitModelEP9Matrix4x35Fix12IiES3_S3_j(shadow, matrix, radius, depth, radius, opacity);
}
