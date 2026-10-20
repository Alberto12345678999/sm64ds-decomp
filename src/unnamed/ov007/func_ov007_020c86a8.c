extern void func_ov007_020c86c4(void *c);
/* c: no class or header names this record (callers 020bf790, 020c8498), so raw. */
void func_ov007_020c86a8(void *c, int v) {
    *(int *)((char *)c + 0x1c) = 0;
    *(int *)((char *)c + 4) = v;
    *(int *)((char *)c + 0x14) = 0;
    func_ov007_020c86c4(c);
}
