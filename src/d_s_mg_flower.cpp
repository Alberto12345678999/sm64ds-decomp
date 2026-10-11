//cpp
/* dScMgFlower_c's factory unit: dScMgFlower_c_classInit and the empty
 * constructor of the class's 0x16-element, 0x20-byte mArray, 2 functions
 * (.text 0x0212b7f8..0x0212b890). The factory allocates the 0x5ff8-byte
 * object and builds it inline, passing the element constructor
 * func_ov006_0212b88c to __cxa_vec_ctor, and the constructor follows it
 * directly in the ROM.
 * Its matching element destructor, func_ov006_0212a650, is in the class's own
 * TU (src/actors/dScMgFlower_c.cpp). `#pragma defer_codegen off` keeps the
 * two functions in ROM order; without it the compiler emits them reversed.
 *
 * leftovers:
 * - dScMgFlower_c_classInit spells the construction sequence out by hand:
 *   `return new dScMgFlower_c()` cannot emit it. mArray is u8[0x2c0] and the
 *   0x51f8 object pad_51f8 is opaque bytes on purpose (include/dScMgFlower_c.h:
 *   a typed element carrying Vec2's destructor would make the compiler add an
 *   implicit pass beside the ROM's __cxa_vec_cleanup), so __cxa_vec_ctor and
 *   func_ov006_020c3f54 stay calls, and the base-subobject C2 plus the two
 *   layered vptr stores only a real ctor emits stay spelled.
 * - func_ov006_0212b88c, func_ov006_0212a650 and func_ov006_020c3f54 keep
 *   their address labels: the mArray element type and the pad_51f8 object
 *   have no recovered class to name members under.
 */
#include "dScMgFlower_c.h"

#pragma defer_codegen off

extern "C" void* _ZN11dScMgBase_cC2Ev(void*);
extern "C" void _ZN8Particle10SysTrackerC1Ev(void*);
extern "C" void __cxa_vec_ctor(void*, int, int, void*, void*);
extern "C" void func_ov006_020c3f54(void*);
extern "C" void func_ov006_0212b88c(void);
extern int _ZTV19dScMgSingle3DBase_c;
extern int _ZTV13dScMgFlower_c;
/* SM64DS proves dScMgFlower_c through RTTI, allocation size, vtable
 * identity, and the MG_FLOWER registry profile; later EAD lineage supplies
 * classInit. Historical alias: func_ov006_0212b7f8. */
extern "C" void* dScMgFlower_c_classInit(void){
  dScMgFlower_c* f = (dScMgFlower_c*)_ZN7fBase_cnwEj(0x5ff8);
  if (f) {
    _ZN11dScMgBase_cC2Ev(f);
    *(void**)f = (void*)&_ZTV19dScMgSingle3DBase_c;
    _ZN8Particle10SysTrackerC1Ev(&f->mSysTracker);
    *(void**)f = (void*)&_ZTV13dScMgFlower_c;
    __cxa_vec_ctor(f->mArray, 0x16, 0x20, (void*)func_ov006_0212b88c, (void*)func_ov006_0212a650);
    func_ov006_020c3f54(f->pad_51f8);
  }
  return f;
}

// @symbol func_ov006_0212b88c
extern "C" void func_ov006_0212b88c(void)
{
}
