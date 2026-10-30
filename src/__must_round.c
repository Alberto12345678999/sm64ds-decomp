#include "types.h"
#include "Decimal.h"
/* MSL __must_round for __rounddec: whether cutting d to
   digits digits rounds up. 1 when the first dropped digit is above 5, or is
   5 with a non-zero digit after it, or is exactly 5 after an odd last kept
   digit (half to even). Otherwise -1. */
int __must_round(const Decimal *d, int digits) {
    const u8 *p = d->sig.text + digits;
    u8 e = *p;
    const u8 *end;
    if (e > 5)
        return 1;
    if (e < 5)
        return -1;
    p = p + 1;
    end = d->sig.text + d->sig.length;
    while (p < end) {
        if (*p != 0)
            return 1;
        p = p + 1;
    }
    return (d->sig.text[digits - 1] & 1) ? 1 : -1;
}
