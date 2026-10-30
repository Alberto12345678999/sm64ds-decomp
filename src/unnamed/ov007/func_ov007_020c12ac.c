/* The 0x10-byte sprite bank func_ov007_020c9688 fills: cellCount 8-byte
 * cells (each a list of packed OAM attributes) and animCount 0x10-byte
 * cell animations. */
typedef struct Ov007SpriteBank {
    int cellCount; /* 0x00 */
    char *cells;   /* 0x04 */
    int animCount; /* 0x08 */
    char *anims;   /* 0x0c */
} Ov007SpriteBank;

extern void *func_ov007_020c3df4(int a, int b);
extern void MultiStore_Int(int val, int *dst, int len);

/* Allocates a sprite bank for `cellCount` cells and `animCount`
 * animations, each table zeroed record by record. */
Ov007SpriteBank *func_ov007_020c12ac(int cellCount, int animCount) {
    Ov007SpriteBank *bank = (Ov007SpriteBank *)func_ov007_020c3df4(0, 0x10);
    bank->cells = (char *)func_ov007_020c3df4(0, cellCount << 3);
    bank->anims = (char *)func_ov007_020c3df4(0, animCount << 4);
    bank->cellCount = cellCount;
    bank->animCount = animCount;
    {
        volatile int v1;
        int i;
        for (i = 0; i < cellCount; i++) {
            v1 = 0;
            MultiStore_Int(v1, (int *)(bank->cells + i * 8), 8);
        }
    }
    {
        volatile int v2;
        int j;
        for (j = 0; j < animCount; j++) {
            v2 = 0;
            MultiStore_Int(v2, (int *)(bank->anims + j * 16), 0x10);
        }
    }
    return bank;
}
