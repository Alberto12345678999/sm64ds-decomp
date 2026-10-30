/* A BG layer as the BG list links it; next as in func_ov007_020c03b0,
 * only the links this file writes. */
typedef struct Ov007BgLayer {
    char pad_00[0x30];
    struct Ov007BgLayer *next; /* 0x30 */
    struct Ov007BgLayer *prev; /* 0x34 */
} Ov007BgLayer;

/* The 0x10-byte BG layer list func_ov007_020c0604 builds (the display
 * record's bgListMain/bgListSub). */
typedef struct Ov007BgList {
    int engines;        /* 0x00: bit 1 main, bit 2 sub */
    int mask;           /* 0x04 */
    Ov007BgLayer *head; /* 0x08 */
    Ov007BgLayer *tail; /* 0x0c */
} Ov007BgList;

/* Appends layer x to the list. c and x keep the callers' int spellings;
 * `list` and `layer` are the typed views. */
void func_ov007_020c0384(int *c, int x) {
    Ov007BgList *list = (Ov007BgList *)c;
    Ov007BgLayer *layer = (Ov007BgLayer *)x;
    if (list->head == 0) {
        list->tail = layer;
        list->head = list->tail;
    } else {
        layer->prev = list->tail;
        list->tail->next = layer;
        list->tail = layer;
    }
}
