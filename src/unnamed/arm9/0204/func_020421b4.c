/* Stop the file-share loader thread (see func_02042200): until
 * func_02058158 reports the thread at data_020a11e4 + 0x400 terminated (state
 * 2), wake it (func_02058048) so that it sees mState cleared and returns, then
 * wait on it (func_0205816c sleeps on its join queue). func_02040aa4 calls this
 * at shutdown. */
extern char data_020a11e4[];
extern int func_02058158(void *p);
extern void func_02058048(void *p);
extern void func_0205816c(void *p);

void func_020421b4(void)
{
    char *base = (char *)(int)data_020a11e4;
    if (func_02058158(base + 0x400)) return;
    do {
        func_02058048(base + 0x400);
        func_0205816c(base + 0x400);
    } while (!func_02058158(base + 0x400));
}
