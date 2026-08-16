#ifndef DAOBJRC_DORIFU_C_H
#define DAOBJRC_DORIFU_C_H

#include "types.h"
#include "daObjDorifu_c.h"

/* class daObjRc_Dorifu_c -- Rc = Rainbow Ride's tricky triangles, built by TrickyTriangles_Spawn at 0x021120c8.
 *
 * Base is daObjDorifu_c, NOT Platform. Its destructor stores three vtables in
 * chain order -- its own, then _ZTV13daObjDorifu_c, then _ZTV8Platform -- and
 * tears down the base's two five-element arrays between the second and third
 * store. TrickyTriangles_Spawn allocates 0xdcc and constructs those same two arrays
 * between the base's vtable store and this class's own.
 *
 * NO MEMBER OF ITS OWN, and here that is a measurement: 0xdcc is where the
 * base's mEventBit ends, so the factory literal leaves this class nothing. Its
 * two siblings allocate the same 0xdcc.
 *
 * Was a flat AUTO-GENERATED struct whose `mModel` at 0xd4 and
 * `mMovingMeshCollider` marker at 0x124 are Platform's own members; both now
 * come from the base, where the collider is the real MovingMeshCollider and is
 * spelled mMeshCollider.
 */

struct daObjRc_Dorifu_c : daObjDorifu_c {
    virtual ~daObjRc_Dorifu_c();

    /* Slots 3 and 0. ActorBase declares both virtuals int-returning. */
    int CleanupResources();
    int InitResources();
};

typedef char daObjRc_Dorifu_c_size_must_be_0xdcc[sizeof(daObjRc_Dorifu_c) == 0xdcc ? 1 : -1];

#endif
