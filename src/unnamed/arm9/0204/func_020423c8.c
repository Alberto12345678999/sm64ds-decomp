extern void OS_WakeupThreadDirect(void *);
extern char data_020a15e4[];

void func_020423c8(void) {
    OS_WakeupThreadDirect(data_020a15e4);
}
