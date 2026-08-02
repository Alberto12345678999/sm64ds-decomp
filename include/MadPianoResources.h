#ifndef MAD_PIANO_RESOURCES_H
#define MAD_PIANO_RESOURCES_H

#include "types.h"

/*
 * Resource evidence from overlay 0's handle table:
 *   0x040a -> data/enemy/piano/piano.bmd
 *   0x040b -> data/enemy/piano/piano.kcl
 *   0x040c -> data/enemy/piano/piano_attack.bca
 *
 * The three BSS objects are eight bytes apart, are initialized by the
 * SharedFilePtr constructor veneers, and are consumed by the corresponding
 * model, mesh-collision, and animation loaders.
 */
typedef struct SharedFilePtrLayout {
    u16 fileID;
    u8 refCount;
    u8 pad_03;
    void *file;
} SharedFilePtrLayout;

typedef char SharedFilePtrLayout_SizeIs8[
    sizeof(SharedFilePtrLayout) == 8 ? 1 : -1
];

/* Readable aliases retain the current linker symbols until a verified rename. */
#define gPianoModelFile             data_ov063_0211ef80
#define gPianoCollisionFile         data_ov063_0211ef88
#define gPianoAttackAnimationFile   data_ov063_0211ef90

#define MAD_PIANO_MODEL_ASSET              0x040a
#define MAD_PIANO_COLLISION_ASSET          0x040b
#define MAD_PIANO_ATTACK_ANIMATION_ASSET   0x040c

#endif
