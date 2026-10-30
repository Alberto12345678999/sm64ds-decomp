#include "types.h"
#include "Decimal.h"

/* MSL __rounddec: cut the significand to length digits, then round up
   (__dorounddecup) when __must_round says so: above half,
   or exactly half with an odd last kept digit. */
extern int __must_round(const Decimal *d, int digits);
extern void __dorounddecup(Decimal *value, int length);

void __rounddec(Decimal *value, int length) {
    int r;
    if (length <= 0)
        return;
    if (length >= value->sig.length)
        return;
    r = __must_round(value, length);
    value->sig.length = length;
    if (r < 0)
        return;
    __dorounddecup(value, length);
}
