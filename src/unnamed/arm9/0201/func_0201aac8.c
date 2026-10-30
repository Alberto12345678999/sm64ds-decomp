/* func_0201aac8 @ 0x201aac8 (arm9) -- tail-call veneer to OS_CreateAlarm (0x2059ba0).
 * ldr ip, [pc]; bx ip; .word 0x2059ba0
 * recovered: the veneer never touches r0, so whatever this function was called
 * with rides straight into OS_CreateAlarm(alarm). func_0201aad4 already passes
 * one argument (through a K&R extern), which is why the empty parameter list
 * was byte-exact and wrong.
 */
struct OSAlarm;
extern void OS_CreateAlarm(struct OSAlarm *alarm);

void func_0201aac8(struct OSAlarm *alarm) {
    OS_CreateAlarm(alarm);
}
