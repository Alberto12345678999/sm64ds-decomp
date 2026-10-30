/* The 0x18-byte sprite group func_ov007_020c3f00 builds; names as there,
 * only the slot this file reads. */
typedef struct Ov007SpriteGroup {
    int *layout; /* 0x00 */
    int root;    /* 0x04: the items' parent node */
} Ov007SpriteGroup;

extern void func_ov007_020c0af4(int *c, int x);

/* Appends the group's root node (and so every item under it) to OAM node
 * list `list`. c keeps the callers' int * spelling. */
void func_ov007_020c3ee8(int *c, int list) {
    Ov007SpriteGroup *grp = (Ov007SpriteGroup *)c;
    func_ov007_020c0af4((int *)list, grp->root);
}
