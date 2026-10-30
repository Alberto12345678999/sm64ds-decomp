#include "types.h"
#include "Decimal.h"

/* MSL __rounddec: cut the significand to length digits, then round up
   (func_02071644) when func_02071698 (__must_round) says so: above half,
   or exactly half with an odd last kept digit. */
extern int func_02071698(const Decimal *d, int digits);
extern void func_02071644(Decimal *value, int length);

void func_020715e0(Decimal *value, int length)
{
    int r;
    if (length <= 0) return;
    if (length >= value->sig.length) return;
    r = func_02071698(value, length);
    value->sig.length = length;
    if (r < 0) return;
    func_02071644(value, length);
}
