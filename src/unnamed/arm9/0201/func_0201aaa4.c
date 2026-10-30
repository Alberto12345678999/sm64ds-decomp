/* func_0201aaa4 @ 0x201aaa4 (arm9) -- tail-call veneer to OS_CancelAlarm (0x2059950).
 * ldr ip, [pc]; bx ip; .word 0x2059950
 * The veneer never touches r0: the alarm it is called with (the watchdog,
 * which begins with its OSAlarm) rides straight into OS_CancelAlarm.
 */
struct OSAlarm;
extern void OS_CancelAlarm(struct OSAlarm *alarm);

void func_0201aaa4(void *alarm) {
    OS_CancelAlarm(alarm);
}
