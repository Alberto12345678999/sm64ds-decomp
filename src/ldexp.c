extern int func_01ff9d40(double, double);
extern double func_01ff8708(double, double);
extern double func_01ff8000(double, double);
extern double copysign(double, double);

static inline int fpclassify_(double x) {
    union { double d; int w[2]; } u;
    u.d = x;
    switch (u.w[1] & 0x7ff00000) {
    case 0x7ff00000:
        if ((u.w[1] & 0xfffff) != 0 || u.w[0] != 0)
            return 1;
        return 2;
    case 0:
        if ((u.w[1] & 0xfffff) != 0 || u.w[0] != 0)
            return 5;
        return 3;
    }
    return 4;
}

/* MSL ldexp (fdlibm scalbn's body): x * 2^n by editing the exponent field.
   Infinity, NaN and zero (the inlined fpclassify) come back as they are. A
   subnormal x is first scaled by 2^54. Overflow returns huge * copysign
   (huge, x) with huge 1e300 and underflow tiny * copysign(tiny, x) with
   tiny 1e-300, so the soft-float multiply raises the right result. */
double ldexp(double x, int n) {
    int hx, lx, k;
    if (fpclassify_(x) <= 2 || x == 0.0) return x;
    hx = ((int*)&x)[1];
    lx = ((int*)&x)[0];
    k = (hx & 0x7ff00000) >> 20;
    if (k == 0) {
        if ((lx | (hx & 0x7fffffff)) == 0) return x;
        x = x * 1.80143985094819840000e+16;
        hx = ((int*)&x)[1];
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000) return 1.0e-300 * x;
    }
    if (k == 0x7ff) return x + x;
    k = k + n;
    if (k > 0x7fe)
        return 1.0e+300 * copysign(1.0e+300, x);
    if (k > 0) {
        ((int*)&x)[1] = (hx & 0x800fffff) | (k << 20);
        return x;
    }
    if (k <= -54) {
        if (n > 50000)
            return 1.0e+300 * copysign(1.0e+300, x);
        else
            return 1.0e-300 * copysign(1.0e-300, x);
    }
    k += 54;
    ((int*)&x)[1] = (hx & 0x800fffff) | (k << 20);
    return 5.55111512312578270212e-17 * x;
}
