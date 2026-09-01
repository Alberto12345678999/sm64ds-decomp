// @symbol daObjWc_Obj03_c_classInit
/* The pinned compiler cannot spell the ROM's folded factory in C++: `new
 * WaterDiamond` calls the unavailable global _Znwm, while the cartridge calls
 * fBase_c::operator new. Placement new and class-specific operator new are
 * rejected by mwccarm 2004/b56 (notes/ctor-migration.md section 5d), so this
 * remains the truthful C transcription of the compiler-generated sequence. */
#include "decl_Actor.h"
#include "decl_ActorBase.h"
#include "decl_Model.h"
#include "decl_dCcAc_c.h"
#include "decl_common.h"
/* recovered: vtable identified, globals resolved */
/* resolved: VT0 = _ZTV12WaterDiamond */
/* Reconstructed source-style name: SM64DS proves daObjWc_Obj03_c through RTTI,
 * allocation size, vtable identity, and the WC_OBJ03 registry profile; later
 * EAD lineage supplies classInit. Exact original spelling is not preserved.
 * The project's WaterDiamond implementation aliases remain unchanged.
 * Historical alias: WaterDiamond_Spawn. */
int *daObjWc_Obj03_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(352);
    if (p) {
        _ZN8dActor_cC2Ev(p);
        p[0] = (int)_ZTV12WaterDiamond;
        _ZN5ModelC1Ev((char *)p + 0xd4);
        _ZN7dCcAc_cC1Ev((char *)p + 0x124);
    }
    return p;
}
