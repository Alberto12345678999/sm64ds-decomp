#ifndef RICKSHAW_BS_H
#define RICKSHAW_BS_H

#include "types.h"
#include "daObjKaitendai_c.h"

/* class RickshawBs -- Bowser in the Sky's rickshaw platform (ov047).
 *
 * Base is daObjKaitendai_c, NOT Platform. Its destructor at 0x021112bc stores
 * three vtables in chain order -- _ZTV10RickshawBs, then ov002:0x021091d4
 * (daObjKaitendai_c's), then _ZTV8Platform -- and only a two-deep chain above
 * it produces three stores.
 *
 * No data member is declared: the destructor destroys Platform's own Model at
 * 0xd4 and MovingMeshCollider at 0x124 and nothing else, so nothing in the
 * matched corpus places a field of this class's own. Absent evidence, not an
 * assertion of emptiness.
 */

struct RickshawBs : daObjKaitendai_c {
    virtual ~RickshawBs();
};

/* NO SIZE ASSERT, deliberately. The obvious evidence is a trap: src/RickshawBs_Spawn.c
 * allocates 816 (0x330), but that function is NOT this class's factory. It stores
 * _ZTV17daObjKurumajiku_c and then _ZTV21daObjKm3_Kurumajiku_c -- a different family
 * entirely (kurumajiku = axle) -- so 0x330 is daObjKm3_Kurumajiku_c's size and says
 * nothing about this class. The four genuine Kaitendai factories each store
 * _ZTV16daObjKaitendai_c then their own vtable and allocate 800; no such factory has
 * been found for this class, so its size is simply not evidenced yet.
 *
 * Pair a class to its factory by VTABLE ADDRESS, never by filename.
 */

#endif
