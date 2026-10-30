// @symbol func_ov007_020c64c4
/* recovered: shared common types, declarations from a shared header */
#include "decl_common.h"
/* recovered: shared common types */
#include "common.h"
#include "Ov007Picker.h"
extern void SubVec3(Vector3 *a, Vector3 *b, Vector3 *c);
extern int LenVec3(Vector3 *a);

/* Re-measures every group's rest links (func_ov007_020c6314 with `b`); in
 * link mode also drops the anchor onto pos and re-measures `link`. The
 * parameter keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is a local. */
void func_ov007_020c64c4(char* c, int b) {
    Ov007Picker *self = (Ov007Picker *)c;
    Ov007Link *link;
    int i;
    for (i = 0; i < self->groupCount; i++) {
        func_ov007_020c6314(c, i, b);
    }
    if (self->mode != 2)
        return;
    self->anchorPos = self->pos;
    link = self->link;
    SubVec3(link->from->target, link->to->target, &link->dir);
    link->length = LenVec3(&link->dir);
}
