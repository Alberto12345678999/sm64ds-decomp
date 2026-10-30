//cpp
extern "C" {

/* The 0xc-byte sprite item this function allocates; names as in
 * func_ov007_020c4090, which resets it. */
typedef struct Ov007SpriteItem {
    void *node;           /* 0x00: its func_ov007_020c11ac node */
    short word4;          /* 0x04 */
    short word6;          /* 0x06 */
    short word8;          /* 0x08 */
    unsigned char margin; /* 0x0a: in pixels (func_ov007_020c3fe4) */
} Ov007SpriteItem;

void *func_ov007_020c11ac(int n);
void *func_ov007_020c3df4(int, int);
void func_ov007_020c4090(Ov007SpriteItem *item);

/* Allocates a sprite item around a fresh OAM node with room for animCount
 * animations, then resets it (func_ov007_020c4090). */
void *func_ov007_020c40d4(int animCount) {
    Ov007SpriteItem *item = (Ov007SpriteItem *)func_ov007_020c3df4(0, sizeof(Ov007SpriteItem));
    item->node = func_ov007_020c11ac(animCount);
    item->word6 = 0;
    item->word4 = item->word6;
    item->margin = 0;
    func_ov007_020c4090(item);
    return item;
}
}
