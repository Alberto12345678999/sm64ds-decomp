extern void func_0201aaa4(void *alarm);
/* Cancel the alarm (func_0201aaa4, OS_CancelAlarm) and return it. */
void *func_0201aab0(void *alarm) {
    func_0201aaa4(alarm);
    return alarm;
}
