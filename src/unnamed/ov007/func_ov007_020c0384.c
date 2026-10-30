#include "Ov007BgLayer.h"

/* Appends layer to the list. */
void func_ov007_020c0384(Ov007BgList *list, Ov007BgLayer *layer) {
    if (list->head == 0) {
        list->tail = layer;
        list->head = list->tail;
    } else {
        layer->prev = list->tail;
        list->tail->next = layer;
        list->tail = layer;
    }
}
