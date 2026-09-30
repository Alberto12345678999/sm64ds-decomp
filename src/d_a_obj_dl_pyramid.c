// @symbol daObjDlPyramid_c_classInit
/* recovered: vtable identified, globals resolved, declarations from a shared header */
#include "decl_ActorBase.h"
#include "decl_Model.h"
#include "decl_Platform.h"
#include "decl_common.h"
/* recovered: vtable identified, globals resolved */
/* resolved: VT0 = _ZTV16daObjDlPyramid_c */
/* Reconstructed source-style name: SM64DS proves daObjDlPyramid_c through RTTI,
 * allocation size, vtable identity, and the DL_PYRAMID registry profile; later
 * EAD lineage supplies classInit. Exact original spelling is not preserved.
 * The implementation class, formerly spelled PyramidTop, now carries the ROM
 * name. Historical alias: PyramidTop_Spawn. */
int *daObjDlPyramid_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(952);
    if (p) {
        _ZN10dBgActor_cC2Ev(p);
        p[0] = (int)_ZTV16daObjDlPyramid_c;
        _ZN5ModelC1Ev((char *)p + 0x320);
    }
    return p;
}
