//cpp
/**
 * Mushroom Roulette minigame scene factory (MG_ROULETTE).
 *
 * This TU is the factory plus its empty element constructor: the
 * factory allocates the scene, runs the base constructor, punches
 * the base then scene vptrs, constructs the particle tracker and the
 * shared table, array-constructs five 0x34-byte entries, and runs
 * both Model constructors. The scene's own methods live in
 * src/actors/dScMgRoulette_c.cpp.
 *
 * deslop
 * Leftover: func_ov006_0210a4ac is an empty 4-byte stub, the
 *   array element constructor; func_ov006_021079c8 is the empty
 *   element destructor owned by the class TU. Naming belongs there.
 * Leftover: func_ov006_020c1d80 is still the linker name of the
 *   shared-table constructor (a per-function file). Naming belongs
 *   at its definition.
 * Leftover: +0x471c is constructed as a Particle SysTracker but has
 *   no named header field; only mTable / mArray are named, so only
 *   those two call sites use members.
 * Leftover: the base C2 is called with no argument, as the ROM does.
 *   The sibling slot1 factory passes the scene; both match, so the
 *   callee's true arity stays open -- do not "fix" either side.
 * Leftover: the hand-rolled allocation stands in for the constructor
 *   that would emit it. No dScMgRoulette_c C1 exists in the ROM, so
 *   `return new` cannot link.
 */

#include "dScMgRoulette_c.h"

extern "C" {
extern "C" void* _ZN7fBase_cnwEj(unsigned int sz);
extern "C" void _ZN11dScMgBase_cC2Ev(void);
extern "C" void _ZN8Particle10SysTrackerC1Ev(char* p);
extern "C" void func_ov006_020c1d80(char* p);
extern "C" void __cxa_vec_ctor(void* p, int a, int b, void* d, void* e);
extern "C" void _ZN5ModelC1Ev(char* p);
extern int _ZTV19dScMgSingle3DBase_c[];
extern int _ZTV15dScMgRoulette_c[];
extern "C" void func_ov006_0210a4ac(void);
}

// @symbol func_ov006_0210a4ac
extern "C" {  /* .c-derived member: C linkage for the whole block */
void func_ov006_0210a4ac(void)
{
}
}

// @symbol dScMgRoulette_c_classInit
/* Reconstructed source-style name: SM64DS proves dScMgRoulette_c through RTTI,
 * allocation size, vtable identity, and the MG_ROULETTE registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. Historical alias: MgMushroomRoulette_Spawn. */
extern "C" void* dScMgRoulette_c_classInit(void){
  dScMgRoulette_c *scene = (dScMgRoulette_c *)_ZN7fBase_cnwEj(0x5400);
  if (scene) {
    char *c = (char *)scene;
    _ZN11dScMgBase_cC2Ev();
    *(int*)c = (int)_ZTV19dScMgSingle3DBase_c;
    _ZN8Particle10SysTrackerC1Ev(c + 0x471c);
    *(int*)c = (int)_ZTV15dScMgRoulette_c;
    func_ov006_020c1d80((char *)scene->mTable);
    __cxa_vec_ctor(scene->mArray, 5, 0x34, func_ov006_0210a4ac, func_ov006_021079c8);
    char* m = c + 0x530c;
    _ZN5ModelC1Ev(m + 0x10);
    _ZN5ModelC1Ev(m + 0x60);
  }
  return scene;
}
