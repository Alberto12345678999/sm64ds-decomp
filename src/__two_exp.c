#include "Decimal.h"

extern unsigned char data_0209a628[];
extern unsigned char data_0209a658[];
extern unsigned char data_0209a680[];
extern unsigned char data_0209a698[];
extern unsigned char data_0209a6a8[];
extern unsigned char data_0209a6b0[];
extern unsigned char data_0209a6b8[];
extern unsigned char data_0209a6c0[];
extern unsigned char data_0209a6c8[];
extern unsigned char data_0209a6cc[];
extern unsigned char data_0209a6d0[];
extern unsigned char data_0209a6d4[];
extern unsigned char data_0209a6d8[];
extern unsigned char data_0209a6dc[];
extern unsigned char data_0209a6e0[];
extern unsigned char data_0209a6e4[];
extern unsigned char data_0209a6e8[];
extern unsigned char data_0209a6ec[];
extern unsigned char data_0209a6f0[];
extern unsigned char data_0209a6f4[];
extern unsigned char data_0209a6f8[];

/* MSL __two_exp: 2^n as a Decimal. n = -64, -53, -32, -16 and -8..8 come
   from the digit strings at data_0209a628..data_0209a6f8 (data_0209a628 is
   "54210108..." with exponent -20, i.e. 2^-64), built by __str2dec.
   Any other n is 2^(n/2) squared (__timesdec, the Decimal multiply),
   times one more 2 or 0.5 when n is odd. __num2dec_internal
   calls it to scale the binary exponent. */
void __str2dec(Decimal *result, unsigned char *digits, short exp);
void __timesdec(Decimal *result, const Decimal *x, const Decimal *y);
void __two_exp(Decimal *out, int n);

void __two_exp(Decimal *out, int n) {
    Decimal half;
    Decimal copy;

    switch (n) {
    case -64:
        __str2dec(out, data_0209a628, -20);
        return;
    case -53:
        __str2dec(out, data_0209a658, -16);
        return;
    case -32:
        __str2dec(out, data_0209a680, -10);
        return;
    case -16:
        __str2dec(out, data_0209a698, -5);
        return;
    case -8:
        __str2dec(out, data_0209a6a8, -3);
        return;
    case -7:
        __str2dec(out, data_0209a6b0, -3);
        return;
    case -6:
        __str2dec(out, data_0209a6b8, -2);
        return;
    case -5:
        __str2dec(out, data_0209a6c0, -2);
        return;
    case -4:
        __str2dec(out, data_0209a6c8, -2);
        return;
    case -3:
        __str2dec(out, data_0209a6cc, -1);
        return;
    case -2:
        __str2dec(out, data_0209a6d0, -1);
        return;
    case -1:
        __str2dec(out, data_0209a6d4, -1);
        return;
    case 0:
        __str2dec(out, data_0209a6d8, 0);
        return;
    case 1:
        __str2dec(out, data_0209a6dc, 0);
        return;
    case 2:
        __str2dec(out, data_0209a6e0, 0);
        return;
    case 3:
        __str2dec(out, data_0209a6e4, 0);
        return;
    case 4:
        __str2dec(out, data_0209a6e8, 1);
        return;
    case 5:
        __str2dec(out, data_0209a6ec, 1);
        return;
    case 6:
        __str2dec(out, data_0209a6f0, 1);
        return;
    case 7:
        __str2dec(out, data_0209a6f4, 2);
        return;
    case 8:
        __str2dec(out, data_0209a6f8, 2);
        return;
    default:
        __two_exp(&half, (int)(n + ((n & 0x80000000u) >> 31)) >> 1);
        __timesdec(out, &half, &half);
        if (n & 1) {
            copy = *out;
            if (n > 0)
                __str2dec(&half, data_0209a6dc, 0);
            else
                __str2dec(&half, data_0209a6d4, -1);
            __timesdec(out, &copy, &half);
        }
        return;
    }
}
