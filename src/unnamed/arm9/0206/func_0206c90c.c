#include "types.h"
typedef struct { int a, b, c, d; } S;
/* The sign of a double: 0x80 if the top byte's sign bit is set, else 0.
   The parameter is spelled as a 16-byte struct, not a double. */
int func_0206c90c(S s){
    char* q = (char*)&s + 7;
    int hi;
    if ((int)q & 1)
        hi = (*(u16*)(q - 1) & 0xff00) >> 8;
    else
        hi = *(u16*)q & 0xff;
    return hi & 0x80;
}
