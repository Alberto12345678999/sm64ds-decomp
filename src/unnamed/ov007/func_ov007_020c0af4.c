/* The 0x44-byte OAM sprite node func_ov007_020c11ac allocates; names as in
 * func_ov007_020c10ec, only the links this file writes. */
typedef struct Ov007OamNode {
    char pad_00[0x3c];
    struct Ov007OamNode *next; /* 0x3c */
    struct Ov007OamNode *prev; /* 0x40 */
} Ov007OamNode;

/* The 0xc-byte OAM node list func_ov007_020c1068 builds (the display
 * record's oamListMain/oamListSub); only the slots this file touches. */
typedef struct Ov007OamList {
    Ov007OamNode *head; /* 0x00 */
    Ov007OamNode *tail; /* 0x04 */
} Ov007OamList;

/* Appends node x to the list. c and x keep the callers' int spellings;
 * `list` and `node` are the typed views. */
void func_ov007_020c0af4(int *c, int x) {
    Ov007OamList *list = (Ov007OamList *)c;
    Ov007OamNode *node = (Ov007OamNode *)x;
    if (list->head == 0) {
        list->tail = node;
        list->head = list->tail;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
}
