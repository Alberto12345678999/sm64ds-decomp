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
   "54210108..." with exponent -20, i.e. 2^-64), built by func_020712a0.
   Any other n is 2^(n/2) squared (func_02071364, the Decimal multiply),
   times one more 2 or 0.5 when n is odd. __num2dec_internal (func_02070c68)
   calls it to scale the binary exponent. */
void func_020712a0(Decimal *result, unsigned char *digits, short exp);
void func_02071364(Decimal *result, const Decimal *x, const Decimal *y);
void func_02070ec0(Decimal *out, int n);

void func_02070ec0(Decimal *out, int n) {
    Decimal half;
    Decimal copy;

    switch (n) {
    case -64: func_020712a0(out, data_0209a628, -20); return;
    case -53: func_020712a0(out, data_0209a658, -16); return;
    case -32: func_020712a0(out, data_0209a680, -10); return;
    case -16: func_020712a0(out, data_0209a698, -5); return;
    case -8:  func_020712a0(out, data_0209a6a8, -3); return;
    case -7:  func_020712a0(out, data_0209a6b0, -3); return;
    case -6:  func_020712a0(out, data_0209a6b8, -2); return;
    case -5:  func_020712a0(out, data_0209a6c0, -2); return;
    case -4:  func_020712a0(out, data_0209a6c8, -2); return;
    case -3:  func_020712a0(out, data_0209a6cc, -1); return;
    case -2:  func_020712a0(out, data_0209a6d0, -1); return;
    case -1:  func_020712a0(out, data_0209a6d4, -1); return;
    case 0:   func_020712a0(out, data_0209a6d8, 0); return;
    case 1:   func_020712a0(out, data_0209a6dc, 0); return;
    case 2:   func_020712a0(out, data_0209a6e0, 0); return;
    case 3:   func_020712a0(out, data_0209a6e4, 0); return;
    case 4:   func_020712a0(out, data_0209a6e8, 1); return;
    case 5:   func_020712a0(out, data_0209a6ec, 1); return;
    case 6:   func_020712a0(out, data_0209a6f0, 1); return;
    case 7:   func_020712a0(out, data_0209a6f4, 2); return;
    case 8:   func_020712a0(out, data_0209a6f8, 2); return;
    default:
        func_02070ec0(&half, (int)(n + ((n & 0x80000000u) >> 31)) >> 1);
        func_02071364(out, &half, &half);
        if (n & 1) {
            copy = *out;
            if (n > 0)
                func_020712a0(&half, data_0209a6dc, 0);
            else
                func_020712a0(&half, data_0209a6d4, -1);
            func_02071364(out, &copy, &half);
        }
        return;
    }
}
