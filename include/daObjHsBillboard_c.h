#ifndef DAOBJHSBILLBOARD_C_H
#define DAOBJHSBILLBOARD_C_H

#include "Model.h"
#include "dActor_c.h"

extern "C" void *_ZN7fBase_cnwEj(unsigned size);

/* Slide decoration billboard. ov031 actors 302-305 share this one class.
 * ROM debug names: HS_MOON / HS_STAR / HS_Y_STAR / HS_B_STAR.
 * overlay_actors.md community names (not synonyms of those debug strings):
 * SLIDE_DECORATION_SILVER_STAR / YELLOW_STAR / ORANGE_SMILEY / BLUE_SMILEY.
 *
 * ROM-proven identity: _ZTI18daObjHsBillboard_c / _ZTS18daObjHsBillboard_c at
 * ov031:0x021118e8/0x021118f4 spell "18daObjHsBillboard_c"; the typeinfo base
 * is _ZTI8dActor_c. Size 0x128 is each factory's operator-new literal.
 * InitResources picks the SharedFilePtr in data_ov031_02111424 from actorID. */

struct daObjHsBillboard_c : dActor_c {
    u8    pad_0d0[0x4];
    Model mModel;          /* 0x0d4 */
    u8    mVariant;        /* 0x124 -- index into data_ov031_02111424 */

    /* InitResources is the first out-of-line virtual/key function. The inline
     * destructor lets mwccarm emit the retail D1/D0 pair and class RTTI/vtable.
     * The inline `~daObjHsBillboard_c() {}` in the
     * header is the whole source of both variants: from an inline body mwcc emits
     * D1 and then D0 -- the cartridge's own order -- and no D2. Written out of
     * line in the source instead they come out D0-before-D1 and the isolation step rejects
     * the object.
     *
     * Both bodies are short because the chain is short: this class's vptr store,
     * then the owned Model at 0xd4, then dActor_c's own teardown, which is where
     * the actor-list unlink lives. D0's trailing deallocation is the inherited
     * inline `operator delete`, which is why nothing in the source names a heap. */
    // @symbol _ZN18daObjHsBillboard_cD1Ev
    // @symbol _ZN18daObjHsBillboard_cD0Ev
    virtual ~daObjHsBillboard_c() {}

    virtual int InitResources();
    virtual int Render();
    virtual int CleanupResources();

    static void *operator new(size_t size);
};

inline void *daObjHsBillboard_c::operator new(size_t size)
{
    return _ZN7fBase_cnwEj((unsigned)size);
}

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char daObjHsBillboard_c_size_must_be_0x128[
    sizeof(daObjHsBillboard_c) == 0x128 ? 1 : -1];
#endif

#endif /* DAOBJHSBILLBOARD_C_H */
