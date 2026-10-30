/* The 0x44-byte OAM sprite node this function allocates; names as in
 * func_ov007_020c10ec, only the slots this file writes. */
typedef struct Ov007OamNode {
    char pad_00[0x18];
    void **anims;            /* 0x18: animCount animations */
    unsigned char animCount; /* 0x1c: func_ov007_020c1180 frees anims only when nonzero */
} Ov007OamNode;

extern void *func_ov007_020c3df4(int a, int b);
extern void func_ov007_020c10ec(void *c);
extern void Sprite_SetAnimation(void *c, int r1, int r2, int r3, int sp0);

/* Allocates an OAM node with room for n animations, resets it
 * (func_ov007_020c10ec) and starts animation 0 looping. */
void *func_ov007_020c11ac(int n) {
    Ov007OamNode *node = (Ov007OamNode *)func_ov007_020c3df4(0, 0x44);
    if (n == 0) {
        node->anims = 0;
    } else {
        node->anims = (void **)func_ov007_020c3df4(0, n * 4);
    }
    func_ov007_020c10ec(node);
    node->animCount = (unsigned char)n;
    Sprite_SetAnimation(node, 0, 1, 0, 0);
    return node;
}
