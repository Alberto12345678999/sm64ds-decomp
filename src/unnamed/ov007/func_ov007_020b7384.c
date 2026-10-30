/* The 0x48-byte 2D display record func_ov007_020b7594 builds; names as
 * there, only the slots this file reads. */
typedef struct Ov007Display {
    char pad_00[0x10];
    const void *oamMain; /* 0x10 */
    const void *oamSub;  /* 0x14 */
} Ov007Display;

/* src/engine/gx/GXS.cpp's OAM copies: 0x07000000 (main) and 0x07000400
 * (sub) plus offset. */
extern void func_020566dc(const void *src, unsigned int offset, unsigned int count);
extern void func_02056674(const void *src, unsigned int offset, unsigned int count);

/* Copies the two 0x400-byte OAM buffers into the main and sub OAM. c keeps
 * the tree's char * spelling; `d` is the typed view. */
void func_ov007_020b7384(char *c) {
    Ov007Display *d = (Ov007Display *)c;
    func_020566dc(d->oamMain, 0, 0x400);
    func_02056674(d->oamSub, 0, 0x400);
}
