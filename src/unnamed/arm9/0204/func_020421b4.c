/* func_020421b4 at 0x020421b4
 *
 * Matched byte-for-byte with mwccarm 1.2/sp2p3 (arm9 main).
 */
extern char data_020a11e4[];
extern int OS_IsThreadTerminated(void *p);
extern void OS_WakeupThreadDirect(void *p);
extern void OS_JoinThread(void *p);

void func_020421b4(void)
{
    char *base = (char *)(int)data_020a11e4;
    if (OS_IsThreadTerminated(base + 0x400))
        return;
    do {
        OS_WakeupThreadDirect(base + 0x400);
        OS_JoinThread(base + 0x400);
    } while (!OS_IsThreadTerminated(base + 0x400));
}
