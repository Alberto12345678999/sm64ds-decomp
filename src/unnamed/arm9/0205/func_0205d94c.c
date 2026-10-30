/* func_0205d94c at 0x0205d94c
 *
 * Tail-call thunk: prepends &data_020a8074 and forwards to FS_LoadArchiveTables.
 */
extern unsigned int FS_LoadArchiveTables(char *thiz, int arg1, unsigned int arg2);

extern int data_020a8074;

int func_0205d94c(int a, int b) {
    return FS_LoadArchiveTables((char *)&data_020a8074, a, b);
}
