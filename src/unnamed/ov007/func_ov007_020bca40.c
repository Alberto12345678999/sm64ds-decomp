#include "Ov007Work.h"

/* The BG layer record; names as in func_ov007_020ad660, only the slots this
 * file sets. */
typedef struct Ov007BgLayer {
    char pad_00[8];
    /* 0x08: func_ov007_020c03b0 uploads and shows the layer only while it is
     * 1 */
    int visible;
    /* 0x0c: func_ov007_020c076c re-uploads the screen while it is set */
    int dirty;
} Ov007BgLayer;

/* The manager's +0x74 display record; only its BG layer table, as in
 * func_ov007_020af434. */
typedef struct Ov007Display {
    char pad_00[0x34];
    Ov007BgLayer **bgLayers; /* 0x34: eight BG layers */
} Ov007Display;

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Shows (1) or hides (0) a set of the eight BG layers, marking each for
 * upload: 0 sets the full layout, 1 hides layer 1, 2 shows layer 0, 3 hides
 * layers 1-3 and shows 4-7. */
void func_ov007_020bca40(int sel) {
    Ov007BgLayer **layers = WORK->display->bgLayers;
    Ov007BgLayer *l;
    switch (sel) {
    case 0:
        l = layers[0];
        l->visible = l->dirty = 0;
        l = layers[1];
        l->visible = l->dirty = 1;
        l = layers[2];
        l->visible = l->dirty = 1;
        l = layers[3];
        l->visible = l->dirty = 1;
        l = layers[4];
        l->visible = l->dirty = 0;
        l = layers[5];
        l->visible = l->dirty = 0;
        l = layers[6];
        l->visible = l->dirty = 1;
        l = layers[7];
        l->visible = l->dirty = 1;
        break;
    case 1:
        l = layers[1];
        l->visible = l->dirty = 0;
        break;
    case 2:
        l = layers[0];
        l->visible = l->dirty = 1;
        break;
    case 3:
        l = layers[2];
        l->visible = l->dirty = 0;
        l = layers[3];
        l->visible = l->dirty = 0;
        l = layers[4];
        l->visible = l->dirty = 1;
        l = layers[5];
        l->visible = l->dirty = 1;
        l = layers[6];
        l->visible = l->dirty = 1;
        l = layers[7];
        l->visible = l->dirty = 1;
        l = layers[1];
        l->visible = l->dirty = 0;
        break;
    }
}
