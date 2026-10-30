#include "Ov007BgLayer.h"

/* Empties a BG layer list. */
void func_ov007_020c05e4(Ov007BgList *list) {
    list->tail = 0;
    list->head = list->tail;
}
