//cpp
/**
 * Smartball minigame scene factory (MG_SMARTBALL).
 *
 * This TU is the factory plus its empty element constructor: the
 * factory allocates the scene, runs the base constructor, stores the
 * vtable word, and array-constructs the four member arrays
 * (mArray1..4). The scene's destructor destroys them in reverse.
 *
 * deslop
 * Leftover: func_ov006_02119900 / func_ov006_0210d894 are empty
 *   4-byte stubs, the mArray4 element constructor / destructor.
 *   Naming belongs at their definitions.
 * Leftover: func_0203d738 / NullDestructor_0203d47c are the shared
 *   arm9 element-ctor/dtor stubs for the 8-byte entries.
 * Leftover: the hand-rolled allocation stands in for the constructor
 *   that would emit it. No dScMgSmartball_c C1 exists in the ROM, so
 *   `return new` cannot link; the base C2 call stays mangled with
 *   the vptr punch.
 */

#include "dScMgSmartball_c.h"

extern "C" {
extern void *_ZN7fBase_cnwEj(unsigned int sz);
extern int _ZN11dScMgBase_cC2Ev(void *p);
extern void __cxa_vec_ctor(void *obj, int a, int b, void *cb1, void *cb2);
extern int _ZTV16dScMgSmartball_c[];
extern void func_0203d738(void);
extern void NullDestructor_0203d47c(void);
extern void func_ov006_02119900(void);
extern void func_ov006_0210d894(void);
void *dScMgSmartball_c_classInit(void);
}

// @symbol func_ov006_02119900
extern "C" void func_ov006_02119900(void)
{
}

// @symbol dScMgSmartball_c_classInit
/* Reconstructed source-style name: SM64DS proves dScMgSmartball_c through RTTI,
 * allocation size, vtable identity, and the MG_SMARTBALL registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. Historical alias: MgBingoBallSlotsShot_Spawn. */
extern "C" void *dScMgSmartball_c_classInit(void) {
    dScMgSmartball_c *scene = (dScMgSmartball_c *)_ZN7fBase_cnwEj(0x629c);
    if (scene != 0) {
        _ZN11dScMgBase_cC2Ev(scene);
        *(int *)scene = (int)_ZTV16dScMgSmartball_c;
        __cxa_vec_ctor(scene->mArray1, 5, 8, (void *)func_0203d738, (void *)NullDestructor_0203d47c);
        __cxa_vec_ctor(scene->mArray2, 0x10, 8, (void *)func_0203d738, (void *)NullDestructor_0203d47c);
        __cxa_vec_ctor(scene->mArray3, 0x10, 8, (void *)func_0203d738, (void *)NullDestructor_0203d47c);
        __cxa_vec_ctor(scene->mArray4, 0x40, 0x24, (void *)func_ov006_02119900, (void *)func_ov006_0210d894);
    }
    return scene;
}
