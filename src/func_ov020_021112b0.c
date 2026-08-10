// @symbol func_ov020_021112b0
/* recovered: shared common types, declarations from a shared header */
#include "decl_common.h"
/* recovered: shared common types */
#include "common.h"
/* Symbols resolved against dsd's relocs.txt: each name below was declared
 * but defined nowhere, so this file could not be linked into the ROM. The
 * replacement is the symbol that already exists at the address the relocation
 * record names for this site; declarations are cloned from the originals so
 * the types -- which decide how the compiler indexes them -- are unchanged.
 *   Actor_ClosestPlayer -> _ZN5Actor13ClosestPlayerEv  (main @ 0x2010ad8)
 *   cstd_atan2 -> _ZN4cstd5atan2E5Fix12IiES1_  (main @ 0x203b4dc)
 */
extern char*_ZN5Actor13ClosestPlayerEv(void*);
extern short _ZN4cstd5atan2E5Fix12IiES1_(int, int);
/* func_ov020_021112b0 at 0x021112b0 (ov020), size 0x90
 * Matched byte-for-byte with mwccarm 1.2/sp2p3.
 * flags: -O4,p -enum int -lang c99 -char signed -interworking -proc arm946e -gccext,on -msgstyle gcc
 */


extern void Vec3_Sub(struct Vector3 *d, struct Vector3 *a, struct Vector3 *b);
extern int Vec3_HorzLen(struct Vector3 *);

void func_ov020_021112b0(char *c)
{
  char *p = _ZN5Actor13ClosestPlayerEv(c);
  if (!p)
    return;
  struct Vector3 *ps = (struct Vector3 *)(((long long)(int)(p + 0x5c)));
  struct Vector3 tmp;
  tmp.x = ps->x;
  tmp.y = ps->y;
  tmp.z = ps->z;
  struct Vector3 d;
  Vec3_Sub(&d, &tmp, (struct Vector3 *)(c + 0x5c));
  *((short *)(c + 0x446)) = _ZN4cstd5atan2E5Fix12IiES1_(d.x, d.z);
  *((short *)(c + 0x444)) = _ZN4cstd5atan2E5Fix12IiES1_(d.y, Vec3_HorzLen(&d));
  *((short *)(c + 0x448)) = 0x4000;
}
