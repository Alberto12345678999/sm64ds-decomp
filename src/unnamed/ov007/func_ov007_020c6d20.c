#include "Ov007StrokePath.h"

extern void func_ov007_020c6d90(char *self, int idx);

extern Ov007StrokePath *func_ov007_020c2a04(Ov007StrokePath *src, int start, int end);
extern void func_ov007_020c281c(Ov007StrokePath *path, int minTurn);
extern void func_ov007_020c27b4(Ov007StrokePath *path);
extern void func_ov007_020c26fc(Ov007StrokePath *path);
extern void func_ov007_020c6e68(char *self, int i);

/* The picker's +0x1c (func_ov007_020c690c's params); only the slot this file
 * reads. */
typedef struct Ov007PickerParams {
    char pad_00[0x18];
    /* 0x18: degrees; func_ov007_020c281c drops each point whose segment
     * turns by less than it (func_ov007_020c2dfc), and a negative value
     * keeps every point */
    int mergeAngle;
} Ov007PickerParams;

/* The 0xd0-byte touch picker func_ov007_020c690c builds; names as in that
 * file, only the slots this function touches. */
typedef struct Ov007Picker {
    char pad_00[0x1c];
    Ov007PickerParams *params; /* 0x1c: func_ov007_020c690c's params */
    Ov007StrokePath *path;     /* 0x20: the stroke being drawn (func_ov007_020c2c68) */
    char pad_24[0x14];
    Ov007StrokePath **groups; /* 0x38: committed strokes */
} Ov007Picker;

typedef char Ov007Picker_size_must_be_0x3c[sizeof(Ov007Picker) == 0x3c ? 1 : -1];

/* Commits the stroke being drawn as group idx: frees what the slot held,
 * copies the path into it, and unless mergeAngle is negative straightens it
 * and recomputes its extrema before building the group's points
 * (func_ov007_020c6e68). The parameter keeps the char * spelling of the
 * callers' declarations; `self` is the typed view. */
void func_ov007_020c6d20(char *picker, int idx) {
    Ov007Picker *self = (Ov007Picker *)picker;
    Ov007StrokePath *src;
    Ov007StrokePath *d;
    int check;

    func_ov007_020c6d90(picker, idx);

    src = self->path;
    self->groups[idx] = func_ov007_020c2a04(src, 0, src->pointCount - 1);

    d = self->groups[idx];
    check = self->params->mergeAngle;
    if (check >= 0) {
        func_ov007_020c281c(d, check);
        func_ov007_020c27b4(d);
        func_ov007_020c26fc(d);
    }

    func_ov007_020c6e68(picker, idx);
}
