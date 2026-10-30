#include "Ov007BgLayer.h"

/* Empties a BG layer list. c keeps the callers' int * spelling. */
void func_ov007_020c05e4(int *c) {
    Ov007BgList *list = (Ov007BgList *)c;
    list->tail = 0;
    list->head = list->tail;
}
