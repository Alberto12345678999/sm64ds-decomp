#include "Ov007Work.h"

/* The BG layer record; names as in func_ov007_020ad660, only the slots this
 * file touches. */
typedef struct Ov007BgLayer {
    char pad_00[0xc];
    /* 0x0c: func_ov007_020c076c re-uploads screen while it is set */
    int dirty;
    void *screen; /* 0x10 */
} Ov007BgLayer;

/* func_ov007_020adc08's 0xc-byte layer slot; names as in that file. */
typedef struct Ov007LayerSlot {
    int state;           /* 0x00 */
    Ov007BgLayer *layer; /* 0x04 */
} Ov007LayerSlot;

extern void func_ov007_020c02d8(void *screen, int rows, unsigned short tile);
extern int func_ov007_020c1d78(int i);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Blanks layer slot 5's screen to tile 0x300 (0x18 rows) and marks it for
 * upload. */
int func_ov007_020adb84(void) {
    Ov007LayerSlot *slot = WORK->layerSlots[5];
    func_ov007_020c02d8(slot->layer->screen, 0x18, 0x300);
    slot->layer->dirty = 1;
    return func_ov007_020c1d78(0);
}
