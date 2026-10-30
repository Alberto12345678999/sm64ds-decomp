//cpp
extern "C" {

/* The 0xc-byte record func_ov007_020c40d4 builds; only the slot this file
 * reads. */
typedef struct Ov007SpriteItem {
    void *node; /* 0x00: its func_ov007_020c11ac node */
} Ov007SpriteItem;

extern void func_ov007_020c1180(void *);
extern void func_ov007_020c3d1c(void *);

/* Frees a func_ov007_020c40d4 record and its node. */
void func_ov007_020c40b4(void *c) {
    Ov007SpriteItem *item = (Ov007SpriteItem *)c;
    func_ov007_020c1180(item->node);
    func_ov007_020c3d1c(c);
}
}
