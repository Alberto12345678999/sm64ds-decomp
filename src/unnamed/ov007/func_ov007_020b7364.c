/* The 0x48-byte 2D display record func_ov007_020b7594 builds; names as
 * there, only the slots this file reads. */
typedef struct Ov007Display {
    char pad_00[8];
    int bgListMain; /* 0x08 */
    int bgListSub;  /* 0x0c */
} Ov007Display;

extern int func_ov007_020c03b0(int);

/* Applies the main and sub BG layer lists (func_ov007_020c03b0). c keeps
 * the tree's char * spelling; `d` is the typed view. */
void func_ov007_020b7364(char *c) {
    Ov007Display *d = (Ov007Display *)c;
    func_ov007_020c03b0(d->bgListMain);
    func_ov007_020c03b0(d->bgListSub);
}
