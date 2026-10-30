/* The manager's +0x74: the 0x48-byte 2D display record. Names as in
 * func_ov007_020ade58, func_ov007_020adc08, func_ov007_020b6d40 and
 * unit020be0dc; each table's count sits in the word before it, and
 * func_ov007_020b73b4 frees every table with its own record's free. */
typedef struct Ov007Display {
    int oamListMain;     /* 0x00: func_ov007_020c1068 node lists */
    int oamListSub;      /* 0x04 */
    int bgListMain;      /* 0x08: func_ov007_020c0604 layer list, engine bit 1 */
    int bgListSub;       /* 0x0c: engine bit 2 */
    int oamMain;         /* 0x10: 0x400-byte OAM buffers (func_ov007_020b7384) */
    int oamSub;          /* 0x14 */
    int transitionCount; /* 0x18 */
    int transitions;     /* 0x1c: func_ov007_020c8b10 records */
    int characterCount;  /* 0x20 */
    int characters;      /* 0x24: func_ov007_020c99d8 records */
    int paletteCount;    /* 0x28 */
    int palettes;        /* 0x2c: func_ov007_020c9988 records */
    int bgLayerCount;    /* 0x30 */
    int bgLayers;        /* 0x34: func_ov007_020c95fc layers */
    int spriteBankCount; /* 0x38 */
    int spriteBanks;     /* 0x3c: func_ov007_020c9688 banks */
    int oamNodeCount;    /* 0x40 */
    int oamNodes;        /* 0x44: func_ov007_020c11ac nodes */
} Ov007Display;

typedef char Ov007Display_size_must_be_0x48[sizeof(Ov007Display) == 0x48 ? 1 : -1];

extern int func_ov007_020c3df4(int a, int b);
extern void func_ov007_020c0354(int (*words)[2], unsigned count);
extern int func_ov007_020c1068(void);
extern int func_ov007_020c0604(int a, int b);

/* Builds the display record: two OAM node lists, a BG layer list per
 * engine (each with its own layer mask) and two cleared 128-entry OAM
 * buffers; every table starts empty. */
int func_ov007_020b7594(int maskMain, int maskSub) {
    Ov007Display *d = (Ov007Display *)func_ov007_020c3df4(0, sizeof(Ov007Display));
    d->oamMain = func_ov007_020c3df4(0, 0x400);
    d->oamSub = func_ov007_020c3df4(0, 0x400);
    func_ov007_020c0354((int(*)[2])d->oamMain, 0x80);
    func_ov007_020c0354((int(*)[2])d->oamSub, 0x80);
    d->oamListMain = func_ov007_020c1068();
    d->oamListSub = func_ov007_020c1068();
    d->bgListMain = func_ov007_020c0604(1, maskMain);
    d->bgListSub = func_ov007_020c0604(2, maskSub);
    d->transitionCount = 0;
    d->transitions = 0;
    d->characterCount = 0;
    d->characters = 0;
    d->paletteCount = 0;
    d->palettes = 0;
    d->spriteBankCount = 0;
    d->spriteBanks = 0;
    d->oamNodeCount = 0;
    d->oamNodes = 0;
    d->bgLayerCount = 0;
    d->bgLayers = 0;
    return (int)d;
}
