#include "Ov007StrokePath.h"
#include "Ov007Picker.h"

extern void func_ov007_020c6d20(char *self, int idx);
extern void func_ov007_020c28ac(void *p);

/* Commits the stroke being drawn as the next group (func_ov007_020c6d20) and
 * clears the path. Returns 0 when there is nothing to commit or no free
 * group, 2 when this commit used the last group, else 1. The parameter keeps
 * the callers' char * spelling; `self` is the typed view. */
int func_ov007_020c6550(char *c)
{
    Ov007Picker *self = (Ov007Picker *)c;
    int status = 1;
    Ov007StrokePath *obj = self->path;
    int left;
    if (obj->pointCount == 0 || (left = *(volatile int *)&self->groupCount) >= self->maxGroups) {
        status = 0;
    } else {
        func_ov007_020c6d20(c, left);
        {
            int *p = &self->groupCount;
            *p = *p + 1;
        }
        if (self->groupCount >= self->maxGroups)
            status = 2;
        func_ov007_020c28ac(obj);
    }
    return status;
}
