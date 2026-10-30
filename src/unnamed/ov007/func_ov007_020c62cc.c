#include "Ov007Picker.h"

/* Re-measures every group's links (func_ov007_020c6174 with b). */
void func_ov007_020c62cc(Ov007Picker *self, int b) {
    int i = 0;
    if (self->groupCount <= 0)
        return;
    do {
        func_ov007_020c6174(self, i, b);
        i++;
    } while (i < self->groupCount);
}
