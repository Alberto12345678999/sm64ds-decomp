#ifndef FLOATINGFLOORLLLBIG_H
#define FLOATINGFLOORLLLBIG_H

#include "types.h"
#include "Platform.h"

/* Derives from Platform: the destructor stores this class's vtable, then
 * Platform's -- inlined -- then destroys the MovingMeshCollider at 0x124 and
 * the Model at 0xd4 before chaining to Actor. All three belong to Platform.
 *
 * ONE FIELD OF ITS OWN. Everything this header used to declare below 0x324 was
 * Actor's and Platform's; unk_324 is the first byte past Platform, which
 * BowserFireSeaArena independently pins by starting its own Model there.
 *
 * The 0x320 that the generated header called an s32 is Platform's, and
 * Platform spells those bytes as two s16. InitResources writes them as one
 * word; see the note in that file.
 */

#ifdef __cplusplus

struct FloatingFloorLllBig : Platform {
    s16 unk_324;            /* 0x324 */

    /* --- vtable --- */
    virtual ~FloatingFloorLllBig();

    int CleanupResources();
    int InitResources();
    int Render();
};

typedef char FloatingFloorLllBig_size_must_be_0x328[sizeof(FloatingFloorLllBig) == 0x328 ? 1 : -1];

#endif /* __cplusplus */

#endif /* FLOATINGFLOORLLLBIG_H */
