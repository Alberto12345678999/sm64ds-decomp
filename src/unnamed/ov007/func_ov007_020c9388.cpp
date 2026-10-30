//cpp
#include "Ov007MenuState.h"

extern "C" {

extern void *func_ov007_020c3df4(const char *name, int size);
extern void func_ov007_020c934c(char *record, int initialState);

void *func_ov007_020c9388(int initialState) {
    char *state = (char *)func_ov007_020c3df4(0, sizeof(Ov007MenuState));
    func_ov007_020c934c(state, initialState);
    return state;
}
}
