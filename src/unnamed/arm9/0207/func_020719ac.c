/* MSL console close for the debug console: nothing to do, returns 0. It
   sits next to __write_console (func_020719b4) and __read_console
   (func_020719ec) in the console handlers of the MSL __files table at
   0x0209a36c. */
int func_020719ac(void)
{
    return 0;
}
