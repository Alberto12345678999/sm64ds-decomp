// Long-branch veneer. #pragma long_calls makes mwccarm emit the pooled
// `ldr ip,[pc]; bx ip` absolute tail-call the ROM uses to reach the target.
#pragma long_calls on

extern void *func_ov007_020c3df4(int a, int b);
extern void func_ov007_020c806c(void *c);
extern int func_ov007_020c3d1c(void);
extern void MultiStore_Int(int val, void *dst, int size);

void *func_ov007_020c80a4(void) {
    void *c = func_ov007_020c3df4(0, 0x18);
    func_ov007_020c806c(c);
    return c;
}

int func_ov007_020c8098(void) {
    return func_ov007_020c3d1c();
}

void func_ov007_020c806c(void *c) {
    volatile int li = 0;
    MultiStore_Int(li, c, 0x18);
}
