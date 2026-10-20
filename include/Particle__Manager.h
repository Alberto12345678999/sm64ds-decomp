#ifndef PARTICLE__MANAGER_H
#define PARTICLE__MANAGER_H

#include "types.h"

namespace Particle {

struct System;

/* One 0x20-byte entry in the manager's effect-definition table. The table
   stride and the leading pointer are fixed by Manager::AddSystem and
   SetSelfDestructFlag; the remaining fields are not reached by either. */
struct SystemDefinition {
    struct Data {
        u32 flags;          /* 0x00 - bit 14 requests self-destruction */
        u32 callbackParam;  /* 0x04 - written by edStarKiraCallback_c */
        u8 pad_008[0x20];
        u16 callbackValue;  /* 0x28 - loaned to a live System */
    };

    Data *data;             /* 0x00 */
    u8 pad_004[0x1c];
};

struct Manager {
    /* The three manager lists are the same two-word intrusive-list heads used
       by func_0204d958/func_0204d9a0. Element types differ. AddSystem names
       the system lists; the third list is the free-particle pool. */
    struct SystemList {
        System *head; /* 0x00 */
        s32 count;    /* 0x04 */
    };

    /* func_0204a4c8 fills this with `b` nodes of 0x44 bytes, and func_02049d60
       hands it to a system. The node is not Particle::Element (0x30). */
    struct FreeList {
        void *head; /* 0x00 */
        s32 count;  /* 0x04 */
    };

    void *allocator;                /* 0x00 */
    SystemList mActiveSystems;      /* 0x04 */
    SystemList mFreeSystems;        /* 0x0c */
    FreeList mFreeParticles;        /* 0x14 */
    SystemDefinition *mDefinitions; /* 0x1c */
    void *unk_020;                  /* 0x20 */
    u16 unk_024;                    /* 0x24 */
    u16 unk_026;                    /* 0x26 */
    u16 unk_028;                    /* 0x28 */
    u16 unk_02a;                    /* 0x2a */
    u16 unk_02c;                    /* 0x2c */
    u16 unk_02e;                    /* 0x2e */
    u8 pad_030[0xc];

    System *AddSystem(int definitionID, Vector3 &position);
};

void SetSelfDestructFlag(u32 definitionID);

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char SystemDefinition_size_must_be_0x20[
    sizeof(SystemDefinition) == 0x20 ? 1 : -1];
typedef char Manager_size_must_be_0x3c[
    sizeof(Manager) == 0x3c ? 1 : -1];
#endif

}

#endif
