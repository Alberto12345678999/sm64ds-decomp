#include "types.h"
#include "Ov007Sprite.h"
#include "Ov007Work.h"
#include "Ov007BgLayer.h"
#include "Ov007Item.h"
#include "Ov007LayerSlot.h"

extern u8 data_ov007_020ccc44[];

extern void func_ov007_020c0288(u16 *p, int count, int val);
extern void func_ov007_020c0638(void *a, int b, int c, int d);
void func_ov007_020b1390(int mode) {
    Ov007Work *g = WORK;
    Ov007BgLayer *p6 = g->layerSlots[1]->layer;
    Ov007Item *p5 = g->itemNodes[7]->item;
    int v;
    char *base;
    /* The byte offsets below are rows 4-5, 10-11 and 14-15 of the 32-tile-wide
     * source map, each from column 3. */
    v = data_ov007_020ccc44[(mode == 0) ? (1) : (0)];
    base = (char *)p6->source;
    func_ov007_020c0288((u16 *)(base + 0x106), 0x20, v);
    base = (char *)p6->source;
    func_ov007_020c0288((u16 *)(base + 0x146), 0x20, v);
    v = data_ov007_020ccc44[(mode == 1) ? (1) : (0)];
    base = (char *)p6->source;
    func_ov007_020c0288((u16 *)(base + 0x286), 0x20, v);
    base = (char *)p6->source;
    func_ov007_020c0288((u16 *)(base + 0x2c6), 0x20, v);
    v = data_ov007_020ccc44[(mode == 2) ? (1) : (0)];
    base = (char *)p6->source;
    func_ov007_020c0288((u16 *)(base + 0x386), 0x20, v);
    base = (char *)p6->source;
    func_ov007_020c0288((u16 *)(base + 0x3c6), 0x20, v);
    func_ov007_020c0638(p6, 0, 0, 0);
    switch (mode) {
    case 0: {
        Ov007ItemLayout *q = p5->layout;
        p5->posX = q->homeX << 0xc;
        p5->posY = 0x28000;
        break;
    }

    case 1: {
        Ov007ItemLayout *q = p5->layout;
        p5->posX = q->homeX << 0xc;
        p5->posY = 0x58000;
        break;
    }

    case 3: {
        Ov007ItemView *r2 = WORK->itemViews[8];
        unsigned int o = r2->sprite->width;
        o = o >> 1;
        o = o + 0xc;
        p5->posX = r2->item->posX - (o << 12);
        p5->posY = 0xa2000;
        break;
    }
    }
}
