
extern double func_01ff8708(double x, double y);
/* MSL frexp (fdlibm's body): split x into a fraction in [0.5, 1) and a
   power of two in *eptr. Zero, infinity and NaN come back as they are with
   *eptr = 0. A subnormal is first scaled by 2^54 (func_01ff8708, the
   soft-double multiply) and the exponent corrected by -54. */
double frexp(double x, int *eptr) {
    int hi = ((int *)(&x))[1];
    int lo = ((int *)(&x))[0];
    int ix;
    *eptr = 0;
    ix = hi & 0x7fffffff;
    if ((ix >= 0x7ff00000) || ((ix | lo) == 0)) {
        return x;
    }
    if (ix < 0x100000) {
        x = func_01ff8708(x, 0x1.0p54);
        hi = ((int *)(&x))[1];
        *eptr = -54;
        ix = hi & 0x7fffffff;
    }
    *eptr += (ix >> 20) - 0x3fe;
    hi = (hi & 0x800fffff) | 0x3fe00000;
    ((int *)(&x))[1] = hi;
    return x;
}
