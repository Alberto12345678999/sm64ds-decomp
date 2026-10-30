#include "types.h"

typedef unsigned long __file_handle;
typedef void (*__idle_proc)(void);

extern void func_02071974(const unsigned char *c);

/* MSL __write_console for the debug console: send *count bytes from buffer
   one at a time through func_02071974, the ARM semihosting SYS_WRITEC call
   (swi 0x123456, r0 = 3). Returns 0. handle and idle_proc are the standard
   proc parameters; the console ignores both. The count is copied into an
   int and compared unsigned: size_t locals do not give the ROM's loop. */
int __write_console(__file_handle handle, unsigned char *buffer, size_t *count,
                    __idle_proc idle_proc) {
    int n = *count;
    int i;
    for (i = 0; (unsigned)i < (unsigned)n; i++) {
        func_02071974(buffer + i);
    }
    return 0;
}
