//cpp
extern "C" {

/* The 0x18-byte sprite group func_ov007_020c3f00 builds; names as there,
 * only the slots this file reads. */
typedef struct Ov007SpriteGroup {
    int *layout;  /* 0x00: [0] is the item count */
    void *root;   /* 0x04: an Ov007OamNode */
    void **items; /* 0x08: layout[0] func_ov007_020c40d4 records */
    void *extra;  /* 0x0c: one more record */
} Ov007SpriteGroup;

extern void func_ov007_020c40b4(void *c);
extern int func_ov007_020c3d1c(void *p);
extern int func_ov007_020c1180(char *c);

/* Frees a sprite group: each item record and their table, the root node,
 * the extra record and the group itself. */
void func_ov007_020c3e7c(char *c) {
    Ov007SpriteGroup *grp = (Ov007SpriteGroup *)c;
    int i;
    for (i = 0; i < *grp->layout; i++) {
        func_ov007_020c40b4(grp->items[i]);
    }
    func_ov007_020c3d1c(grp->items);
    func_ov007_020c1180((char *)grp->root);
    func_ov007_020c40b4(grp->extra);
    func_ov007_020c3d1c(c);
}
}
