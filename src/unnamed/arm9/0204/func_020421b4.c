/* Stop the file-share loader thread (see func_02042200): until
 * func_02058158 reports the thread at data_020a11e4 + 0x400 terminated (state
 * 2), wake it (func_02058048) so that it sees mState cleared and returns, then
 * wait on it (func_0205816c sleeps on its join queue). func_02040aa4 calls this
 * at shutdown. */
extern char data_020a11e4[];
/* local extern: the thread is untyped storage here (void *) */
extern int OS_IsThreadTerminated(void *p);
/* local extern: as above */
extern void OS_WakeupThreadDirect(void *p);
/* local extern: as above */
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
