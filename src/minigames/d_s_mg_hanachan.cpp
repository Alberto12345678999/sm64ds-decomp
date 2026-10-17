//cpp
/* Which Wiggler (MG_HANACHAN): the scene factory and the constructor for
 * the five 8-byte entries inside each of its fifteen 0x98-byte elements.
 * The scene's own methods are in src/minigames/d_s_mg_hanachan_methods.cpp.
 *
 * leftovers:
 *   - dScMgHanachan_c has no constructor declared, so the factory builds
 *     the object by hand: operator new, base constructor, vtable word
 *     (data_ov006_0213cab8 is _ZTV15dScMgHanachan_c), array construction.
 *   - The plain Wiggler and Point records describe the observed layout.
 *     Their lifecycle callbacks retain their scalar ABI and manual array
 *     construction; the five points begin at +0x18.
 */

#include "dScMgHanachan_c.h"

extern "C" {
extern void *_ZN11dScMgBase_cC2Ev(void *p);
extern void __cxa_vec_ctor(void *obj, int a, int b, void *cb1, void *cb2);
extern int data_ov006_0213cab8[];
void *dScMgHanachan_c_classInit(void);
/* local extern: only sibling minigame headers (dScMgAmida_c.h and four
   others) declare it; this TU includes none of them */
extern void NullDestructor_0203d47c(void);
extern void func_0203d738(void);
}

// @symbol Wiggler_Construct
extern "C" void *Wiggler_Construct(char *elem) {
    __cxa_vec_ctor(((dScMgHanachan_c::Wiggler *)elem)->seg, 5, 8, (void *)func_0203d738,
                   (void *)NullDestructor_0203d47c);
    return elem;
}

// @symbol dScMgHanachan_c_classInit
extern "C" void *dScMgHanachan_c_classInit(void) {
    char *scene = (char *)fBase_c::operator new(0x4f68);
    if (scene != 0) {
        _ZN11dScMgBase_cC2Ev(scene);
        *(int *)scene = (int)data_ov006_0213cab8;
        __cxa_vec_ctor(((dScMgHanachan_c *)scene)->mWiggler, 0xf, 0x98, (void *)Wiggler_Construct,
                       (void *)Wiggler_Destroy);
    }
    return scene;
}
