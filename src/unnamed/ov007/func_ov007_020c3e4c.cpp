//cpp

extern "C" {
extern void OS_FreeToHeap(int idx, int sel, void *arg);

void func_ov007_020c3e4c(void *arg) {
    OS_FreeToHeap(0, -1, arg);
}
}
