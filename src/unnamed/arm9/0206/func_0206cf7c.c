/* Test mask against the debugger flags word at 0x027fff74 (word 5 of the
   block at 0x027fff60). The console and overlay code read bits 1, 4, 0x2000
   and 0x20000. */
int func_0206cf7c(int mask)
{
    int *base = (int *)0x027fff60;
    return (mask & base[5]) ? 1 : 0;
}
