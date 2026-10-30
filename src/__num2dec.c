#include "types.h"
#include "Decimal.h"

/* MSL __num2dec: convert x to a Decimal of at most f->digits significant
 * digits (capped at 32), then turn the digit values into ASCII. decform is
 * MSL's layout, as in float2str.c, which calls this. */
typedef struct {
    char style;
    char unused;
    short digits;
} decform;

void __num2dec_internal(void *out, double x);
void __rounddec(void *thiz, int val);

#pragma opt_strength_reduction off
void __num2dec(void *a0, double x, void *d) {
    int n;
    Decimal *c = (Decimal *)d;
    int i;
    n = ((decform *)a0)->digits;
    __num2dec_internal(c, x);
    if (c->sig.text[0] > 9) /* inf or nan: no digits to round */
        return;
    if (n > 0x20) n = 0x20;
    __rounddec(c, n);
    while (c->sig.length < n) {
        c->sig.text[c->sig.length++] = 0;
    }
    c->exp -= c->sig.length - 1;
    for (i = 0; i < c->sig.length; i++) {
        c->sig.text[i] += '0';
    }
}
