#include "types.h"
/* NitroSDK mystrlen (mb_gameinfo.c): length of a NUL-terminated u16
   string, in characters. MBi_MakeGameInfo sizes the game name and
   introduction with it. */
int mystrlen(const u16 *str) {
    int count = 0;

    while (*str++ != 0) {
        count++;
    }
    return count;
}
