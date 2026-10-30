struct OSAlarm;
extern void func_0201aac8(struct OSAlarm *alarm);
/* Create the alarm x (func_0201aac8, OS_CreateAlarm) and return it. The
   watchdog's constructor func_0201aa18 starts with it. */
int func_0201aad4(int x) {
    func_0201aac8((struct OSAlarm *)x);
    return x;
}
