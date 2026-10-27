//cpp
#include "types.h"
#include "dActor_c.h"

extern "C" {

// func_0200e55c - find cutscene object by owner ID
extern u32 data_0209b2a4[];

struct dActor_c* func_0200e55c(u32 ownerID) {
    u32* ids = data_0209b2a4;
    int i = 0;
    struct dActor_c* a;
    do {
        a = dActor_c::FindWithID(*ids);
        if (a && ownerID == a->param1)
            return a;
        i++;
        ids++;
    } while (i < 0x10);
    return 0;
}
}
