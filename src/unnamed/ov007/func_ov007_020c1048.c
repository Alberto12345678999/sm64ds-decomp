/* The 0xc-byte OAM node list; names as in func_ov007_020c0af4, which
 * appends to it. Nothing in ov007 touches its third word. */
typedef struct Ov007OamList {
    void *head; /* 0x00 */
    void *tail; /* 0x04 */
    char pad_08[4];
} Ov007OamList;

extern void *func_ov007_020c3df4(int a, int b);
extern void func_ov007_020c1048(int *c);
extern int func_ov007_020c3d1c(void);

/* Builds an empty OAM node list. */
void *func_ov007_020c1068(void) {
    void *c = func_ov007_020c3df4(0, sizeof(Ov007OamList));
    func_ov007_020c1048(c);
    return c;
}

/* Frees an OAM node list. Long-branch veneer: long_calls emits the pooled
 * `ldr ip,[pc]; bx ip` absolute tail-call; bracketed because the pragma is
 * positional. */
#pragma long_calls on
int func_ov007_020c105c(void) {
    return func_ov007_020c3d1c();
}
#pragma long_calls off

/* Empties an OAM node list. c keeps the callers' int * spelling. */
void func_ov007_020c1048(int *c) {
    Ov007OamList *list = (Ov007OamList *)c;
    list->tail = 0;
    list->head = list->tail;
}
