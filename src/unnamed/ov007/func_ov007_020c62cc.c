#include "Ov007Picker.h"

extern void func_ov007_020c6174(Ov007Picker *t, int idx, int flag);

/* Re-measures every group's links (func_ov007_020c6174 with b). a keeps the
 * char * spelling of the callers' declarations. */
void func_ov007_020c62cc(char *a, int b) {
    Ov007Picker *self = (Ov007Picker *)a;
    int i = 0;
    if (self->groupCount <= 0)
        return;
    do {
        func_ov007_020c6174(self, i, b);
        i++;
    } while (i < self->groupCount);
}
