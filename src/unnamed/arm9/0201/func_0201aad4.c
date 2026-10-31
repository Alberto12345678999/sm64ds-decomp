struct OSAlarm;
extern void func_0201aac8(struct OSAlarm *alarm);
/* Create the alarm (func_0201aac8, OS_CreateAlarm) and return it. The
   watchdog's constructor func_0201aa18 starts with it. */
void *func_0201aad4(void *alarm) {
    func_0201aac8(alarm);
    return alarm;
}
