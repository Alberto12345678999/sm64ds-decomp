//cpp
/* cstd -- the tree's C++ namespace of math wrappers: the division-unit
 * routines (mod/div/fdiv/ldiv plus the async/result pairs) and the
 * square-root-unit helpers that live in the same contiguous run, arm9
 * 0x02052ef4..0x02053274, 13 functions. The file takes the class name the
 * tree already uses for the namespace (shard file names, decl_common.h
 * externs), per Juan 2026-10-11.
 *
 * mwccarm emits .text in reverse source order here, so definitions run from
 * the highest address (fdiv) down to the lowest (mod); each earlier
 * definition is the declaration its callers need, with the remaining
 * callees forward-declared below. The two Fix12-taking routines keep the
 * shards' extern "C" spelling under their identical identifiers: in C they
 * define the mangled identifier verbatim, and the mangled symbol comes out
 * identical in the C++ TU.
 */
#include "types.h"
#include "nitro/hw/registers.h"

namespace cstd {
int mod(int a, int b);
int div(int a, int b);
int fdiv_result(void);
long long ldiv_result(void);
long long ldiv(int a, int b);
int fdiv(int numerator, int denominator);
}

extern "C" {
void _ZN4cstd10fdiv_asyncE5Fix12IiE5Fix12IiE(int a, int b);
void _ZN4cstd16reciprocal_asyncE5Fix12IiE(int a);
int _ZN4cstd11fdiv_resultEv(void);
long long _ZN4cstd11ldiv_resultEv(void);
int func_02052fdc(void);
void func_02053008(int n);
}

// @symbol _ZN4cstd4fdivEii
namespace cstd {

s32 fdiv(s32 numerator, s32 denominator)
{
    _ZN4cstd10fdiv_asyncE5Fix12IiE5Fix12IiE(numerator, denominator);
    return _ZN4cstd11fdiv_resultEv();
}

}

// @symbol _ZN4cstd4ldivEii
namespace cstd {

long long ldiv(int a, int b)
{
  _ZN4cstd10fdiv_asyncE5Fix12IiE5Fix12IiE(a, b);
  while(*(volatile unsigned short*)0x4000280 & 0x8000);
  return *(volatile long long*)0x40002a0;
}

}

// @symbol func_02053200
extern "C" {
s32 func_02053200(s32 x)
{
    _ZN4cstd16reciprocal_asyncE5Fix12IiE(x);
    return _ZN4cstd11fdiv_resultEv();
}
}

// @symbol func_020531a4
extern "C" {
int func_020531a4(int a)
{
    volatile unsigned short *ime = (volatile unsigned short *)0x4000208;
    volatile int *div = (volatile int *)0x40002b8;
    unsigned short saved;
    if (a <= 0) return 0;
    saved = *ime;
    *ime = 0;
    *(volatile unsigned short *)0x40002b0 = 1;
    div[0] = 0;
    div[1] = a;
    *ime;
    *ime = saved;
    return func_02052fdc();
}
}

// @symbol func_02053130
extern "C" {
s32 func_02053130(s32 r0)
{
    s32 r4 = r0;
    s64 divres;
    volatile u16 *sqrtcnt;
    s32 r2;

    if (r4 <= 0)
        goto ret_zero;

    _ZN4cstd16reciprocal_asyncE5Fix12IiE(r4);
    func_02053008(r4);
    divres = _ZN4cstd11ldiv_resultEv();

    sqrtcnt = &REG_SQRTCNT;
    while (*sqrtcnt & SQRT_CONTROL_BUSY)
        ;

    r2 = 0;
    return (s32)((divres * (s64)REG_SQRT_RESULT + ((s64)r2 + (s64)0x200) * (s64)(1LL << 32)) >> (32 + 10));

ret_zero:
    return 0;
}
}

// @symbol _ZN4cstd11ldiv_resultEv
namespace cstd {

long long ldiv_result(void)
{
  while(*(volatile unsigned short*)0x4000280 & 0x8000);
  return *(volatile long long*)0x40002a0;
}

}

// @symbol _ZN4cstd11fdiv_resultEv
namespace cstd {

int fdiv_result(void)
{
  while(*(volatile unsigned short*)0x4000280 & 0x8000);
  return (int)((*(volatile long long*)0x40002a0 + 0x80000) >> 20);
}

}

// @symbol _ZN4cstd16reciprocal_asyncE5Fix12IiE
extern "C" {
void _ZN4cstd16reciprocal_asyncE5Fix12IiE(int a){
  *(volatile unsigned short*)0x4000280 = 1;
  *(volatile unsigned long long*)0x4000290 = ((unsigned long long)0x1000) << 32;
  *(volatile unsigned long long*)0x4000298 = (unsigned)a;
}
}

// @symbol func_02053008
extern "C" {
void func_02053008(int n)
{
    volatile unsigned short *r208 = (volatile unsigned short *)0x4000208;
    volatile unsigned short *r2b0 = (volatile unsigned short *)0x40002b0;
    volatile unsigned int *r2b8 = (volatile unsigned int *)0x40002b8;
    unsigned short old;
    if (n > 0) {
        old = *r208;
        *r208 = 0;
        *r2b0 = 1;
        r2b8[0] = 0;
        r2b8[1] = n;
        *r208;
        *r208 = old;
    } else {
        old = *r208;
        *r208 = 0;
        *r2b0 = 1;
        r2b8[0] = 0;
        r2b8[1] = 0;
        *r208;
        *r208 = old;
    }
}
}

// @symbol func_02052fdc
extern "C" {
int func_02052fdc(void) {
    while (*(volatile unsigned short *)0x40002b0 & 0x8000)
        ;
    return (*(volatile unsigned int *)0x40002b4 + 0x200) >> 10;
}
}

// @symbol _ZN4cstd10fdiv_asyncE5Fix12IiE5Fix12IiE
extern "C" {
void _ZN4cstd10fdiv_asyncE5Fix12IiE5Fix12IiE(int a, int b){
  *(volatile unsigned short*)0x4000280 = 1;
  *(volatile unsigned long long*)0x4000290 = ((unsigned long long)(unsigned)a) << 32;
  *(volatile unsigned long long*)0x4000298 = (unsigned)b;
}
}

// @symbol _ZN4cstd3divEii
namespace cstd {

int div(int a, int b)
{
  *(volatile unsigned short*)0x4000280 = 0;
  *(volatile int*)0x4000290 = a;
  *(volatile unsigned long long*)0x4000298 = (unsigned)b;
  while(*(volatile unsigned short*)0x4000280 & 0x8000);
  return *(volatile int*)0x40002a0;
}

}

// @symbol _ZN4cstd3modEii
namespace cstd {

int mod(int a, int b)
{
  *(volatile unsigned short*)0x4000280 = 0;
  *(volatile int*)0x4000290 = a;
  *(volatile unsigned long long*)0x4000298 = (unsigned)b;
  while(*(volatile unsigned short*)0x4000280 & 0x8000);
  return *(volatile int*)0x40002a8;
}

}
