//cpp
/**
 * Slot-machine minigame scene factory (MG_SLOT1).
 *
 * This TU is the factory only: it allocates the scene, runs the base
 * constructor, punches the scene and bet-icon vptrs, and runs the two
 * embedded-object initializers the class TU owns. The scene's own
 * methods live in src/actors/dScMgSlot1_c.cpp.
 *
 * deslop
 * Leftover: func_ov006_0210c2b0 / func_ov006_0210c208 are still
 *   linker names of the embedded-object initializers owned by the
 *   class TU. Naming belongs there.
 * Leftover: the three vptr stores stand in for the constructor that
 *   would emit them. No dScMgSlot1_c C1 exists in the ROM, so
 *   `return new` cannot link; the base C2 call is explicit for the
 *   same reason.
 * Leftover: pad_4684 / pad_4690 / pad_469c are embedded objects of
 *   unknown type (header); only mBetIcon is typed.
 */

#include "dScMgSlot1_c.h"

extern "C" {
extern void *_ZN7fBase_cnwEj(unsigned int sz);
extern void _ZN11dScMgBase_cC2Ev(void *);
extern void func_ov006_0210c2b0(char *p);
extern void func_ov006_0210c208(char *p);
extern void *_ZTV12dScMgSlot1_c;
extern void *_ZTVN12dScMgSlot1_c9betIcon_cE;
extern void *_ZTV9dThIcon_c;
void *dScMgSlot1_c_classInit(void);
/* Reconstructed source-style name: SM64DS proves dScMgSlot1_c through RTTI,
 * allocation size, vtable identity, and the MG_SLOT1 registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. Historical alias: func_ov006_0210d6b8. */
void *dScMgSlot1_c_classInit(void)
{
    dScMgSlot1_c *scene =
        (dScMgSlot1_c *)_ZN7fBase_cnwEj(sizeof(dScMgSlot1_c));
    if (scene) {
        _ZN11dScMgBase_cC2Ev(scene);
        *(void **)scene = &_ZTV12dScMgSlot1_c;
        dScMgSlot1_c::betIcon_c *icon = &scene->mBetIcon;
        *(void **)icon = &_ZTV9dThIcon_c;
        *(void **)icon = &_ZTVN12dScMgSlot1_c9betIcon_cE;
        func_ov006_0210c2b0((char *)scene->pad_4684);
        func_ov006_0210c2b0((char *)scene->pad_4690);
        func_ov006_0210c208((char *)scene->pad_469c);
    }
    return scene;
}
}
