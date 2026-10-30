//cpp

extern "C" {
extern void OS_AllocFromHeap(int idx, int sel, void *arg);

void func_ov007_020c3e64(void *arg) {
    OS_AllocFromHeap(0, -1, arg);
}
}
