extern int func_ov007_020b3f20(int n);
extern int func_ov007_020b2308(int a, int b);

/* data_ov007_0210342c: the overlay's manager; names as in
 * func_ov007_020b9880 and func_ov007_020b4c04, only the slots this function
 * builds. */
typedef struct Ov007Work {
    char pad_00[0x78];
    int textures[11]; /* 0x78: one per func_ov007_020b2308 call below */
} Ov007Work;

extern struct Ov007Work *data_ov007_0210342c;
void func_ov007_020b697c(void)
{
    int i;
    int n = func_ov007_020b3f20(0x16);
    for (i = 0; i < 0xb; i++) {
        int r = func_ov007_020b2308(n, i);
        data_ov007_0210342c->textures[i] = r;
    }
}
