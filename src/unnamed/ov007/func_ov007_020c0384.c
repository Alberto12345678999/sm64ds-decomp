#include "Ov007BgLayer.h"

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
