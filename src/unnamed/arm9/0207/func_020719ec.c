#include "types.h"
extern unsigned char func_02071988(void);

/* MSL __read_console for the debug console: read up to *pcount bytes into
   buf through func_02071988, the ARM semihosting SYS_READC call (swi
   0x123456, r0 = 7). A CR or LF ends the read and *pcount becomes the count
   including it. Returns 0. */
int func_020719ec(int unused, unsigned char *buf, unsigned int *pcount)
{
    unsigned int i;
    unsigned int n = *pcount;
    i = 0;
    while (i < n) {
        unsigned char c;
        buf[i] = func_02071988();
        c = buf[i];
        if (c == 0xd || c == 0xa) {
            *pcount = i + 1;
            break;
        }
        i++;
    }
    return 0;
}
