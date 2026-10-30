/* The 0x10-byte BG layer list; names as in func_ov007_020c0384, only the
 * slots this file writes. */
typedef struct Ov007BgList {
    char pad_00[8];
    void *head; /* 0x08 */
    void *tail; /* 0x0c */
} Ov007BgList;

/* Empties a BG layer list. c keeps the callers' int * spelling. */
void func_ov007_020c05e4(int *c) {
    Ov007BgList *list = (Ov007BgList *)c;
    list->tail = 0;
    list->head = list->tail;
}
