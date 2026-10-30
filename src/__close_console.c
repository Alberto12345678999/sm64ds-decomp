/* MSL __close_console for the debug console: nothing to do, returns 0. It
   is the close_proc after __read_console and __write_console in each of the
   three console FILEs of the MSL __files table at 0x0209a36c. */
int __close_console(void) {
    return 0;
}
