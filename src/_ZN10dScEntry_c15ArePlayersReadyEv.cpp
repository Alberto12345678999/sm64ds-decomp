//cpp
#include "dScEntry_c.h"
extern "C" {
extern u8 data_0209fc5c[];
u8 func_02020364(int player);
}
int dScEntry_c::ArePlayersReady() {
    int player = 0;
    u8 *active = data_0209fc5c;
    for (;;) {
        if (*active != 0) {
            int ready = func_02020364(player);
            if (ready == 0)
                return 0;
        }
        ++player;
        ++active;
        if (player >= 4)
            break;
    }
    return 1;
}
