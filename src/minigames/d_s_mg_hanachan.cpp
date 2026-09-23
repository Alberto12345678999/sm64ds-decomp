//cpp
/**
 * Which-Wiggler minigame scene factory (MG_HANACHAN).
 *
 * This TU is the factory plus its array-construction helper: the
 * factory allocates the scene, runs the base constructor, stores the
 * vtable word, and array-constructs the fifteen 0x98-byte elements at
 * +0x4678; func_ov006_020ede80 array-constructs the five 8-byte
 * entries at each element's +0x18. The scene's own methods live in
 * src/actors/dScMgHanachan_c.cpp.
 *
 * deslop
 * Leftover: func_ov006_020ea324 is still the linker name of the
 *   0x98-byte element constructor owned by the class TU (its struct C
 *   names the +0x18 entries v18). Naming belongs there.
 * Leftover: func_0203d738 / NullDestructor_0203d47c are the shared
 *   arm9 element-ctor/dtor stubs; the 8-byte entries' own type is
 *   unrecovered, so +0x18 stays a raw offset here.
 * Leftover: data_ov006_0213cab8 is the vtable word store (symbols.txt
 *   names _ZTV15dScMgHanachan_c at the same address). Spelling the
 *   _ZTV name would add an import this factory-only TU does not
 *   otherwise need, so the data spelling stays.
 * Leftover: the hand-rolled allocation stands in for the constructor
 *   that would emit it (base C2, vtable word, array construction).
 *   The base C2 call stays mangled with the vptr punches.
 */

extern "C" {
extern void *_ZN7fBase_cnwEj(unsigned int sz);
extern int _ZN11dScMgBase_cC2Ev(void *p);
extern void __cxa_vec_ctor(void *obj, int a, int b, void *cb1, void *cb2);
extern int data_ov006_0213cab8[];
extern void func_ov006_020ea324(void *);
void *dScMgHanachan_c_classInit(void);
extern void NullDestructor_0203d47c(void);
extern void func_0203d738(void);
}

// @symbol func_ov006_020ede80
extern "C" void* func_ov006_020ede80(char* self)   /* `this` is a keyword in C++ */
{
    __cxa_vec_ctor(self + 0x18, 5, 8, (void*)func_0203d738, (void*)NullDestructor_0203d47c);
    return self;
}

// @symbol dScMgHanachan_c_classInit
/* Reconstructed source-style name: SM64DS proves dScMgHanachan_c through RTTI,
 * allocation size, vtable identity, and the MG_HANACHAN registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. Historical alias: MgWhichWiggler_Spawn. */
extern "C" void *dScMgHanachan_c_classInit(void) {
    char *o = (char *)_ZN7fBase_cnwEj(0x4f68);
    if (o != 0) {
        _ZN11dScMgBase_cC2Ev(o);
        *(int *)o = (int)data_ov006_0213cab8;
        __cxa_vec_ctor(o + 0x4678, 0xf, 0x98, (void *)func_ov006_020ede80, (void *)func_ov006_020ea324);
    }
    return o;
}
