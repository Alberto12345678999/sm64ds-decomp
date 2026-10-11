//cpp
/* engine/collision/CLPS_BlockRef.cpp — CLPS_BlockRef TU
 * (arm9 0x0203821c..0x02038298)
 *
 * CLPS_BlockRef is the one-word value handle dBgW_Kc carries: a raw
 * CLPS_Block pointer with value semantics. The TU is the three member
 * definitions below plus func_02038234, the free helper that ends the
 * run above them: it gates on func_02038298, indexes the enabled-collider
 * table data_020a0c80 with dBgPi's collider index and dispatches the
 * entry's stored callback. mwccarm emits the constructor's C1,C2 pair
 * and the destructor's D2,D1 pair (no D0 -- nothing deletes a
 * CLPS_BlockRef, and the type is non-polymorphic). Source order is the
 * helper, then constructor, destructor, then operator= so the deferred
 * emission order lands the ROM's operator=, D1, C1, func_02038234 layout
 * (mwccarm emits .text in reverse source order).
 */
#include "CLPS_BlockRef.h"
#include "dBgPi.h"

extern "C" {
int func_02038298(int a, int b);
int func_020393bc(int *p);
int func_020393b4(int *p);
}
extern dBgW *data_020a0c80[];

typedef void (*PFN)(int self, int arg, int b);

// @symbol func_02038234
extern "C" void func_02038234(int a, int b)
{
    int idx;
    dBgW *entry;
    PFN fn;
    if (func_02038298(a, b) == 0) return;
    idx = ((dBgPi *)a)->GetColliderIndex();
    entry = data_020a0c80[idx];
    fn = (PFN)func_020393bc((int *)entry);
    if (fn == 0) return;
    fn((int)entry, func_020393b4((int *)entry), b);
}

// @symbol _ZN13CLPS_BlockRefC1Ev
CLPS_BlockRef::CLPS_BlockRef() : ptr(0) {}

// @symbol _ZN13CLPS_BlockRefD1Ev
CLPS_BlockRef::~CLPS_BlockRef() {}

// @symbol _ZN13CLPS_BlockRefaSER10CLPS_Block
CLPS_BlockRef &CLPS_BlockRef::operator=(CLPS_Block &block)
{
    ptr = &block;
    return *this;
}
