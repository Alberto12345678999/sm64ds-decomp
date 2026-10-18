//cpp
#include "dBgCh.h"
#include "dActor_c.h"

// @symbol _ZN5dBgCh8SetActorEP8dActor_c
void dBgCh::SetActor(dActor_c *actor)
{
    if (!actor) {
        mOwner = 0;
        mOwnerUniqueID = -1;
    } else {
        mOwner = actor;
        mOwnerUniqueID = actor->uniqueID;
    }
}
