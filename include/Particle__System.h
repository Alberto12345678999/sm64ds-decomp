#ifndef PARTICLE__SYSTEM_H
#define PARTICLE__SYSTEM_H

#include "Particle__Manager.h"
#include "Particle__SysTracker.h"

namespace Particle {

struct System {
    struct Flags {
        u32 unk_000 : 6;
        u32 unk_006 : 6;
        u32 unk_00c : 6;
        u32 unused  : 14;
    };

    u8 pad_000[0x18];
    SystemDefinition *mDefinition; /* 0x18 */
    /* Callback virtuals toggle bit 1 while spawning or suppressing particles. */
    u32 callbackFlags;             /* 0x1c */
    u8 pad_020[0x1a];
    /* simpleCallback_c copies this value in both directions. */
    s16 callbackValue;             /* 0x3a */
    u8 pad_03c[0x0c];
    /* Descriptive names for callback-owned, body-proven fields. */
    s32 callbackParam;             /* 0x48 */
    s32 callbackVelocity;          /* 0x4c */
    s32 callbackScale;             /* 0x50 */
    u8 pad_054[0x20];
    Flags flags;                   /* 0x74 */

    static System *FromUniqueID(u32 uniqueID);
};

typedef char System_size_must_be_0x78[sizeof(System) == 0x78 ? 1 : -1];

}

extern "C" Particle::SysTracker *data_0209ee74;

#endif
