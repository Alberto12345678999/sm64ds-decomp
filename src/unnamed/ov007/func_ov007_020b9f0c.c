#include "types.h"
#include "Ov007MenuState.h"
#include "Ov007StrokePath.h"

extern void func_ov007_020c6550(void* o);
extern void func_ov007_020c5c14(void* o, void* p);
extern void func_ov007_020c5ef0(void* o);
extern void func_ov007_020c510c(char* c);
extern char** data_ov007_02104ba0;
extern int* data_ov007_02104b9c;

/* The 0xd0-byte touch picker func_ov007_020c690c builds; names as in that
 * file, only the slots this file touches. */
typedef struct Ov007Picker {
    char pad_00[0x20];
    Ov007StrokePath *path; /* 0x20: the stroke being drawn (func_ov007_020c2c68) */
    char pad_24[0x4c];
    Vector3 pos; /* 0x70: posPoint's position */
} Ov007Picker;

/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates; names
 * as in func_ov007_020ba05c and func_ov007_020b9ca8, only the slots this
 * file touches. */
typedef struct Ov007PickerScene {
    Ov007Picker *picker;       /* 0x00: func_ov007_020c690c */
    Ov007MenuState *states[4]; /* 0x04: func_ov007_020c9388; [1] is the main one */
    char pad_14[0x14];
    int idleFrames; /* 0x28: frames with no touch and no key; func_ov007_020b8fb4 tests >= 0xf0 */
} Ov007PickerScene;

typedef char Ov007Picker_size_must_be_0x7c[sizeof(Ov007Picker) == 0x7c ? 1 : -1];
typedef char Ov007PickerScene_size_must_be_0x2c[sizeof(Ov007PickerScene) == 0x2c ? 1 : -1];

/* The extern keeps its char ** spelling; the typed view is reached through a
 * cast macro. */
#define SCENE ((Ov007PickerScene*)data_ov007_02104ba0)

/* Commits a stroke still being drawn, settles the picker, clears the
 * requests on states[2] and [3] and presets idleFrames to its 0xf0 limit. */
void func_ov007_020b9f0c(void)
{
    if (SCENE->picker->path->pointCount != 0) {
        func_ov007_020c6550(SCENE->picker);
    }
    func_ov007_020c5c14(SCENE->picker, &SCENE->picker->pos);
    func_ov007_020c5ef0(SCENE->picker);
    func_ov007_020c510c((char *)SCENE->picker);

    SCENE->idleFrames = 0;
    SCENE->states[2]->requestedState = 0;
    SCENE->states[3]->requestedState = 0;
    SCENE->idleFrames = 0xf0;
    *data_ov007_02104b9c = 0x1000;
}
