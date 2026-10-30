#include "Ov007Picker.h"

extern void func_ov007_020c4fcc(int r0, int r1);
/* The definition takes half as s16; declared that way, the call does not match. */
extern void func_ov007_020c19cc(int count, Vector3 *pts, int half, int t);

/* Draws the committed strokes up to the draw limit through
 * func_ov007_020c19cc: each whole group before limitGroup at full progress,
 * then limitGroup itself cut at limitIndex points and limitFraction.
 * c keeps the char * spelling of the callers' declarations; `self` is the
 * typed view. The loop test reads limitGroup volatile: plain, the function
 * compiles 4 bytes short (either read alone being volatile matches). */
void func_ov007_020c4dfc(char *c, int r1, int r2, int r3)
{
    Ov007Picker *self = (Ov007Picker *)c;
    func_ov007_020c4fcc(r2, r3);
    int i = 0;
    while (i < *(volatile int *)&self->limitGroup) {
        Ov007StrokePath **a38 = self->groups;
        Vector3 **a28 = self->groupPoints;
        func_ov007_020c19cc(a38[i]->pointCount, a28[i], r1, 0x1000);
        i++;
    }
    {
        int m = self->limitGroup;
        if (m < self->groupCount) {
            Vector3 **a28 = self->groupPoints;
            func_ov007_020c19cc(self->limitIndex, a28[m], r1, self->limitFraction);
        }
    }
}
