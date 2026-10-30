
extern int data_0209cddc;
extern void func_02013f28(void);
/* The exception handler main installs (OS_SetUserExceptionHandler), which
   Crash calls too: keep v in data_0209cddc, then stop for good in the
   fatal-error spin (func_02013f28). */
void func_0201a03c(int v) {
    data_0209cddc = v;
    func_02013f28();
}