/* The 0x2c-byte item func_ov007_020aea6c allocates; names as there, only
 * the slot this file reads. */
typedef struct Ov007Item {
    char pad_00[4];
    void *state; /* 0x04: func_ov007_020c9388(1) */
} Ov007Item;

extern void func_ov007_020c937c(void *state);
extern int func_ov007_020c3d1c(void *);

/* Frees an item: its menu state, then the record. c keeps the callers'
 * char * spelling; the int return is the free hook's tail call. */
int func_ov007_020aea4c(char *c) {
    Ov007Item *item = (Ov007Item *)c;
    func_ov007_020c937c(item->state);
    return func_ov007_020c3d1c(c);
}
