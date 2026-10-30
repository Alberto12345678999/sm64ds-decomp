#include "Ov007Work.h"
#include "Ov007BgLayer.h"

extern int func_ov007_020c3df4(int a, int b);
extern int func_ov007_020c9388(int a);
extern int func_ov007_020b8500(void);
extern int func_ov007_020b84e8(void);
extern void func_ov007_020c0384(int c, void *x);
extern int func_ov007_020b84f4(void);
extern void func_ov007_020c02d8(int r0, int r1, unsigned short r2);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* The manager's +0x74: the 0x48-byte 2D display record func_ov007_020b7594
 * allocates. Only its two BG layer lists, which func_ov007_020c0604 creates
 * for engine bit 1 (main) and 2 (sub) and func_ov007_020c0384 appends to. */
typedef struct Ov007Display {
    char pad_00[8];
    int bgListMain; /* 0x08 */
    int bgListSub;  /* 0x0c */
} Ov007Display;

/* The 0xc-byte record this function returns; func_ov007_020b6d40 keeps the
 * eight of them from the manager's +0xc8. */
typedef struct Ov007LayerSlot {
    int state;           /* 0x00: an Ov007MenuState (func_ov007_020c9388) */
    Ov007BgLayer *layer; /* 0x04 */
    char kind;           /* 0x08: func_ov007_020b6d40's slot index, 0..7 */
} Ov007LayerSlot;

typedef char Ov007LayerSlot_size_must_be_0xc[sizeof(Ov007LayerSlot) == 0xc ? 1 : -1];
typedef char Ov007Display_size_must_be_0x10[sizeof(Ov007Display) == 0x10 ? 1 : -1];

/* Builds layer slot `type` around `obj` and links obj into the main or sub
 * BG list: 6/7 take prebuilt screen pairs, 1 keeps the loaded screen as its
 * source behind a fresh buffer, 5 starts from a blank (tile 0x300) screen. */
int func_ov007_020adc08(int type, char *obj) {
    int r5 = func_ov007_020c3df4(0, 0xc);
    Ov007LayerSlot *slot = (Ov007LayerSlot *)r5;
    Ov007BgLayer *layer = (Ov007BgLayer *)obj;
    Ov007Display *display = WORK->display;
    slot->kind = (char)type;
    slot->layer = layer;
    slot->state = func_ov007_020c9388(0);
    switch (type) {
    case 6:
        layer->screen = (void *)func_ov007_020b8500();
        layer->source = (void *)func_ov007_020b84e8();
        func_ov007_020c0384(display->bgListMain, obj);
        break;
    case 7:
        layer->screen = (void *)func_ov007_020b84f4();
        layer->source = (void *)func_ov007_020b84e8();
        func_ov007_020c0384(display->bgListSub, obj);
        break;
    case 1:
        layer->source = layer->screen;
        layer->screen = (void *)func_ov007_020c3df4(0, 0x800);
        func_ov007_020c0384(display->bgListMain, obj);
        break;
    case 2:
        func_ov007_020c0384(display->bgListSub, obj);
        break;
    case 3:
    case 4:
        func_ov007_020c0384(display->bgListSub, obj);
        break;
    case 5:
        layer->screen = (void *)func_ov007_020c3df4(0, 0x800);
        func_ov007_020c02d8((int)layer->screen, 0x18, 0x300);
        func_ov007_020c0384(display->bgListSub, obj);
        break;
    default:
        break;
    }
    return r5;
}
