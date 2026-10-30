#include "Ov007Picker.h"

extern void func_ov007_020c28ac(void* a);

/* Resets the picker: when flag is set frees every group slot
 * (func_ov007_020c6d90), then clears the path and both counts. */
void func_ov007_020c6724(Ov007Picker *picker, int flag) {
    if (flag != 0) {
        int i;
        for (i = 0; i < picker->maxGroups; i++) {
            func_ov007_020c6d90(picker, i);
        }
    }
    func_ov007_020c28ac(picker->path);
    picker->groupCount = 0;
    picker->totalPoints = 0;
}
