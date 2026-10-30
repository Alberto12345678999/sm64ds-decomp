#include "Ov007StrokePath.h"
#include "Ov007Picker.h"

extern int func_ov007_020c3ce4(void);
extern void func_ov007_020c6724(void *self, int flag);
extern void func_ov007_020c6e68(void *self, int i);
extern int func_ov007_020c5db0(void *c);

/* Loads a whole drawing into the picker as count committed strokes: resets
 * it (func_ov007_020c6724), builds stroke i from the coordinate tables
 * (mode 0 int coordinates, func_ov007_020c2b38; mode 1 byte coordinates,
 * func_ov007_020c2acc) and its spring chain (func_ov007_020c6e68), then
 * sets groupCount and totalPoints. */
void func_ov007_020c6784(void *object, int count, const int *pointCounts, const void *xCoords,
                         const void *yCoords, const int *const *progressThresholds, int mode) {
    Ov007Picker *self = (Ov007Picker *)object;
    int i;
    func_ov007_020c3ce4();
    func_ov007_020c6724(self, 1);
    /* Each mode interprets the coordinate-pointer tables in its own format. */
    for (i = 0; i < count; i++) {
        switch (mode) {
        case 0:
            self->groups[i] = (Ov007StrokePath *)func_ov007_020c2b38(
                pointCounts[i], ((const int *const *)xCoords)[i], ((const int *const *)yCoords)[i],
                progressThresholds[i]);
            break;
        case 1:
            self->groups[i] = (Ov007StrokePath *)func_ov007_020c2acc(
                pointCounts[i], ((const unsigned char *const *)xCoords)[i],
                ((const unsigned char *const *)yCoords)[i], progressThresholds[i]);
            break;
        }
        func_ov007_020c6e68(self, i);
    }
    self->groupCount = count;
    self->totalPoints = func_ov007_020c5db0(self);
    func_ov007_020c3ce4();
}
