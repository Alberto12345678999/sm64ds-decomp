#include "Ov007Work.h"
#include "Ov007BgLayer.h"

extern int func_ov007_020c0638(void *p, int a, int b, int d);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* The 0xc-byte layer slot func_ov007_020adc08 returns; names as in that
 * file. */
typedef struct Ov007LayerSlot {
    int state;           /* 0x00 */
    Ov007BgLayer *layer; /* 0x04 */
} Ov007LayerSlot;

/* Resets the scroll of layer slots 6 and 1 and rebuilds both screens from
 * their sources at a y offset of -0xc0 pixels (func_ov007_020c0638). */
void func_ov007_020b131c(void) {
    Ov007Work *work = WORK;
    Ov007BgLayer *a = work->layerSlots[6]->layer;
    Ov007BgLayer *b = work->layerSlots[1]->layer;
    a->scrollX = 0;
    a->scrollY = 0;
    a->fineScrollY = 0;
    a->fineScrollX = a->fineScrollY;
    b->scrollX = 0;
    b->scrollY = 0;
    b->fineScrollY = 0;
    b->fineScrollX = b->fineScrollY;
    func_ov007_020c0638(a, 0, -0xc0, 0);
    func_ov007_020c0638(b, 0, -0xc0, 0);
}
