/* func_0201aaa4 @ 0x201aaa4 (arm9) -- tail-call veneer to OS_CancelAlarm (0x2059950).
 * ldr ip, [pc]; bx ip; .word 0x2059950
 */
extern void OS_CancelAlarm(void);

void func_0201aaa4(void) {
    OS_CancelAlarm();
}
