/* The 0x10-byte sprite bank func_ov007_020c12ac allocates; names as
 * there. */
typedef struct Ov007SpriteBank {
    int cellCount; /* 0x00 */
    char *cells;   /* 0x04: 8-byte cells */
    int animCount; /* 0x08 */
    char *anims;   /* 0x0c: 0x10-byte cell animations */
} Ov007SpriteBank;

extern void func_ov007_020c13f4(char *p);
extern void func_ov007_020c3d1c(void *p);
extern int func_ov007_020c1384(char *c);

/* Frees a sprite bank: each cell's OAM list (func_ov007_020c13f4), each
 * animation's tables (func_ov007_020c1384), both tables and the bank. */
void func_ov007_020c121c(char *c) {
    Ov007SpriteBank *bank = (Ov007SpriteBank *)c;
    int i;
    int j;
    for (i = 0; i < bank->cellCount; i++) {
        func_ov007_020c13f4(bank->cells + i * 8);
    }
    func_ov007_020c3d1c(bank->cells);
    for (j = 0; j < bank->animCount; j++) {
        func_ov007_020c1384(bank->anims + j * 0x10);
    }
    func_ov007_020c3d1c(bank->anims);
    func_ov007_020c3d1c(c);
}
