//cpp
/* arm9/cstd2 -- cstd::sqrt(u64) alone at .text 0x0203d744..0x0203d7b8,
 * folded from one legacy shard. The division-unit cstd TU (arm9/cstd at
 * 0x02052ef4..0x02053274) is not contiguous with this address, so the
 * square-root-unit wrapper is its own original file. The span is bounded
 * on both sides by unnamed helpers: func_0203d740 ends at 0x0203d744
 * below and func_0203d7b8 begins at 0x0203d7b8 above. Single definition,
 * so emission order is trivially ROM-ascending.
 */

// @symbol _ZN4cstd4sqrtEy
//
// Language-mode flip only: the compiler mangles the name, it is no longer
// spelled by hand. Signature and body preserved exactly; no codegen intent.
// See notes/plan-cpp-language-mode.md phase 1 (layout-free SDK namespaces).
namespace cstd {

int sqrt(unsigned long long x)
{
  volatile unsigned short *ime = (volatile unsigned short*)0x4000208;
  unsigned short saved = *ime;
  *ime = 0;
  *(volatile unsigned short*)0x40002b0 = 1;
  *(volatile unsigned long long*)0x40002b8 = x << 2;
  *ime;
  *ime = saved;
  while(*(volatile unsigned short*)0x40002b0 & 0x8000);
  return (*(volatile int*)0x40002b4 + 1) >> 1;
}

}
