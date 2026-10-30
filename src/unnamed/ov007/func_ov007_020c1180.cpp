//cpp
extern "C" {

/* The 0x44-byte OAM sprite node func_ov007_020c11ac allocates; names as in
 * func_ov007_020c10ec, only the slots this file reads. */
typedef struct Ov007OamNode {
    char pad_00[0x18];
    void **anims;            /* 0x18: animCount animations */
    unsigned char animCount; /* 0x1c */
} Ov007OamNode;

extern int func_ov007_020c3d1c(void *p);

/* Frees an OAM node and, when it has any, its animation table. */
int func_ov007_020c1180(char *c) {
    Ov007OamNode *node = (Ov007OamNode *)c;
    if (node->animCount) {
        func_ov007_020c3d1c(node->anims);
    }
    return func_ov007_020c3d1c(c);
}
}
