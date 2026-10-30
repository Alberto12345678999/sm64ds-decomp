#include "Ov007OamNode.h"

/* Appends node to the list. */
void func_ov007_020c0af4(Ov007OamList *list, Ov007OamNode *node) {
    if (list->head == 0) {
        list->tail = node;
        list->head = list->tail;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
}
