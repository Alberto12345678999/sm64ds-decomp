/* The 0x10-byte BG layer list; names as in func_ov007_020c0384. */
typedef struct Ov007BgList {
    int engines; /* 0x00: bit 1 main, bit 2 sub (func_ov007_020c03b0) */
    int mask;    /* 0x04: the layers func_ov007_020c03b0 applies */
    void *head;  /* 0x08 */
    void *tail;  /* 0x0c */
} Ov007BgList;

extern int *func_ov007_020c3df4(int, int);
extern void func_ov007_020c05e4(int *);

/* Builds an empty BG layer list for `engines` and `mask`. */
int *func_ov007_020c0604(int engines, int mask) {
    Ov007BgList *list = (Ov007BgList *)func_ov007_020c3df4(0, sizeof(Ov007BgList));
    func_ov007_020c05e4((int *)list);
    list->engines = engines;
    list->mask = mask;
    return (int *)list;
}
