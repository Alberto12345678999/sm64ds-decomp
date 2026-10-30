#include "Ov007Picker.h"

/* Sums the progress threshold of each committed group's last point (the
 * progress func_ov007_020c65bc recorded when it appended that point). */
int func_ov007_020c5d5c(Ov007Picker *self) {
    int i;
    int sum = 0;
    for (i = 0; i < self->groupCount; i++) {
        Ov007StrokePath *group = self->groups[i];
        sum += group->progressThresholds[group->pointCount - 1];
    }
    return sum;
}
