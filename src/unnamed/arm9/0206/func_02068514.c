#include "types.h"
/* Length of a NUL-terminated u16 string, in characters. func_02068680
   sizes the game name and introduction with it. */
int func_02068514(u16 *p)
{
    u16 v = *p++;
    int count = 0;
    while (v != 0) {
        v = *p++;
        count++;
    }
    return count;
}
