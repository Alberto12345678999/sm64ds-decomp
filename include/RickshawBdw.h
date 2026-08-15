#ifndef RICKSHAWBDW_H
#define RICKSHAWBDW_H

#include "types.h"
#include "daObjKurumajiku_c.h"

/* class RickshawBdw -- Bowser in the Dark World's rickshaw axle (ov043).
 * The ROM's RTTI calls it daObjKm1_Kurumajiku_c (ov043:0x02112338); its vtable
 * is the one the tree already spells _ZTV11RickshawBdw at 0x0211238c.
 *
 * Base is daObjKurumajiku_c, NOT Platform. Its destructor stores three vtables
 * in chain order -- _ZTV11RickshawBdw, then _ZTV17daObjKurumajiku_c, then
 * _ZTV8Platform -- and RickshawBdw_Spawn allocates 816 = 0x330 and stores the
 * intermediate's vtable before its own. Both sides agree.
 *
 * NO MEMBER OF ITS OWN, and here that is a measurement rather than an absence
 * of evidence: 0x330 is where daObjKurumajiku_c's own four-ID array ends, so the
 * factory literal leaves this class exactly nothing. Its sibling
 * daObjKm3_Kurumajiku_c allocates the same 816.
 *
 * Its own vtable adds slots 0 and 3 (func_ov043_021114c4, func_ov043_021114b0)
 * and the destructor pair, and overrides nothing else.
 */

struct RickshawBdw : daObjKurumajiku_c {
    virtual ~RickshawBdw();
};

typedef char RickshawBdw_size_must_be_0x330[sizeof(RickshawBdw) == 0x330 ? 1 : -1];

#endif
