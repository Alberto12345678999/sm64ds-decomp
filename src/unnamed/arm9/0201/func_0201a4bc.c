extern void OS_SleepThread(void *);
extern char data_0209d4fc[];
extern char data_0209d500[];

/* Sleep until the next VBlank: IRQ::VBlankHandler wakes data_0209d4fc's
   queue on every one. */
void func_0201a4d0(void) {
    OS_SleepThread(data_0209d4fc);
}

/* The main loop's frame wait: sleep on data_0209d500's queue, which
   IRQ::VBlankHandler wakes every data_0208ee44 VBlanks while data_0209d4f0
   (func_020197b8 raises it around this wait) is up. */
void func_0201a4bc(void) {
    OS_SleepThread(data_0209d500);
}
