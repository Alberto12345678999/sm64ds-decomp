#ifndef DAOBJWANWANSHUTTER_C_H
#define DAOBJWANWANSHUTTER_C_H

#include "types.h"
#include "dBgW_KcMbg.h"

/* Derives from dBgActor_c: the destructor stores this class's vtable, then
 * dBgActor_c's -- inlined -- then destroys the dBgW_KcMbg at 0x124 and
 * the Model at 0xd4 before chaining to dActor_c. All three belong to dBgActor_c.
 * Everything this header used to restate below 0x31e was dActor_c's and
 * dBgActor_c's, and is inherited now.
 *
 * SIZE IS THE OBSERVED FIELD SPAN, rounded up. It guards this declaration; it
 * is not independent evidence about the ROM.
 */

#include "dBgActor_c.h"

struct daObjWanwanShutter_c : dBgActor_c {
    u8 mDisabled;                     /* 0x31e -- both Behavior and Render return immediately while it is set */

    /* --- vtable --- */
    /* MEASURED -- INLINE ON PURPOSE, do not move out of line.
     * Out of line, mwccarm 2004/b56 emits D0 before D1 (the reverse of the
     * cartridge's 0x02112e0c D1 / 0x02112e50 D0) and a homeless D2, and
     * objisolate rejects the whole translation unit. Defined in the class
     * body it emits D1 then D0 and no D2, which is the ROM's own order.
     *
     * Safe here because the class is a LEAF: the only word in the cartridge
     * pointing at _ZTI20daObjWanwanShutter_c (ov014 0x02114868) is its own
     * vtable header at 0x021148ac, so nothing derives from it.
     *
     * The body is empty but the FUNCTION IS NOT: at 0x44 bytes it inlines
     * dBgActor_c's own inline destructor, which destroys the Model at 0xd4
     * and the dBgW_KcMbg at 0x124. Do not write those members as padding.
     */
    virtual ~daObjWanwanShutter_c() {}

    int Behavior();
    int CleanupResources();
    int InitResources();
    int Render();
};

typedef char daObjWanwanShutter_c_size_must_be_0x320[sizeof(daObjWanwanShutter_c) == 0x320 ? 1 : -1];

#endif /* DAOBJWANWANSHUTTER_C_H */
