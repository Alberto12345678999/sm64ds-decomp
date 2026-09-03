// @symbol daBgSnwmn_c_classInit
/* recovered: vtable identified, declarations from a shared header */
#include "decl_Actor.h"
#include "decl_ActorBase.h"
#include "decl_Model.h"
#include "decl_dCcAcPos_c.h"
#include "decl_ShadowModel.h"
#include "decl_TextureSequence.h"
#include "decl_common.h"
extern int _ZTV11daBgSnwmn_c[];
/* recovered: vtable identified */
/* vtable identified: VT0 = _ZTV11daBgSnwmn_c */
/* Reconstructed source-style name. ROM evidence proves the daBgSnwmn_c
 * class, factory shape, allocation size, vtable, and registry relationship;
 * the exact original SM64DS factory spelling does not survive. */
int *daBgSnwmn_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(496);
    if (p) {
        _ZN8dActor_cC2Ev(p);
        p[0] = (int)_ZTV11daBgSnwmn_c;
        _ZN5ModelC1Ev((char *)p + 0xd4);
        _ZN5ModelC1Ev((char *)p + 0x124);
        _ZN15TextureSequenceC1Ev((char *)p + 0x174);
        _ZN11ShadowModelC1Ev((char *)p + 0x188);
        _ZN10dCcAcPos_cC1Ev((char *)p + 0x1b0);
    }
    return p;
}
