//cpp
#include "types.h"
#include "dActor_c.h"

extern "C" {

// func_0200e6d8 - find player actor by parameter
extern u8 data_0209f250;
extern struct dActor_c* data_0209f394[];
extern u32 data_0209b284[];

struct dActor_c* func_0200e6d8(u32 arg0) {
    struct dActor_c* player;
    struct dActor_c* result;

    player = data_0209f394[data_0209f250];
    if (arg0 == player->param1) {
        result = player;
    } else {
        result = dActor_c::FindWithID(data_0209b284[arg0]);
    }
    return result;
}
}
