//cpp
#include "Ov007MenuState.h"
#include "Ov007Sprite.h"
#include "cstd.h"

extern "C" {

extern void *data_ov007_02104b9c;
extern void *data_ov007_02104ba0;

/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates; names
 * as in func_ov007_020b91b4, only the slots this function touches. */
typedef struct Ov007PickerScene {
    void *picker;              /* 0x00: func_ov007_020c690c */
    Ov007MenuState *states[4]; /* 0x04: func_ov007_020c9388; [1] is the main one */
    char pad_14[0x28];
    s32 tweenOut[2]; /* 0x3c: bound as tweens[i]->out (func_ov007_020c908c) */
} Ov007PickerScene;

/* data_ov007_02104b9c: the 0x14 record of the scene's sprites
 * (func_ov007_020b9880); names as in func_ov007_020b91b4. */
typedef struct Ov007PickerSprites {
    char pad_00[4];
    Ov007Sprite *sprites[4]; /* 0x04: func_ov007_020c44e4 */
} Ov007PickerSprites;

int func_ov007_020b9fc0(void) {
    Ov007PickerSprites *base = (Ov007PickerSprites *)data_ov007_02104b9c;
    Ov007Sprite *p1 = base->sprites[0];
    Ov007Sprite *p2 = base->sprites[1];
    s32 *addr4 = &p2->alpha;
    s32 *addr1 = &p1->alpha;

    if (*addr1 < 0x1f000) {
        Ov007PickerScene *c = (Ov007PickerScene *)data_ov007_02104ba0;
        if (c->states[1]->currentState == 5) {
            *addr1 = 0x1f000;
        }
    } else {
        *addr4 -= 0x1000;
        if (*addr4 <= 0) {
            *addr4 = 0;
        }
    }

    ((Ov007PickerScene *)data_ov007_02104ba0)->tweenOut[1] = cstd::div(*addr4, 0x1f);

    return (*addr4 == 0) ? 1 : 0;
}
}
