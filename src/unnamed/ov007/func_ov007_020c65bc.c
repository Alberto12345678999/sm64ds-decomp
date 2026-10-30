#include "types.h"
#include "Ov007StrokePath.h"

extern int func_ov007_020c25fc(Ov007StrokePath *path, int x, int y, int minLen, int maxLen,
                               int minTurn);
extern void func_ov007_020bfe4c(char *camera, int x, int y, int z, Vector3 *out);

/* The picker's +0x1c (func_ov007_020c690c's params); only the point thresholds
 * this file hands to func_ov007_020c25fc. */
typedef struct Ov007PickerParams {
    char pad_00[8];
    int minLen;  /* 0x08: pixels between appended points */
    int maxLen;  /* 0x0c */
    int minTurn; /* 0x10: degrees; a gentler turn drops the point */
} Ov007PickerParams;

/* The 0xd8-byte camera func_ov007_020c023c allocates; names as in
 * func_ov007_020c0128, only the slot this file reads. */
typedef struct Ov007Camera {
    char pad_00[0x2c];
    int distance; /* 0x2c */
} Ov007Camera;

/* The 0xd0-byte touch picker func_ov007_020c690c builds; names as there and
 * in func_ov007_020c6724, only the slots this file touches. */
typedef struct Ov007Picker {
    char pad_00[0x10];
    int maxPoints;   /* 0x10 */
    int totalPoints; /* 0x14 */
    char pad_18[4];
    Ov007PickerParams *params; /* 0x1c */
    Ov007StrokePath *path;     /* 0x20 */
    Vector3 *pathPoints;       /* 0x24 */
    char pad_28[0x80];
    Ov007Camera *camera; /* 0xa8 */
} Ov007Picker;

/* Appends screen point (x, y), in pixels, to the stroke being drawn. When
 * func_ov007_020c25fc takes it, the point gets `progress` as its progress
 * threshold and is unprojected through the camera, at the camera's
 * distance, into pathPoints. Returns 1 if the point was added, 0 if it was
 * refused and 2 once maxPoints is reached. t keeps the callers' char *
 * spelling; `p` is the typed view. */
int func_ov007_020c65bc(char *t, int x, int y, int progress) {
    Ov007Picker *p = (Ov007Picker *)t;
    int ret = 0;
    Ov007StrokePath *path = p->path;
    if (p->totalPoints < p->maxPoints) {
        int last = path->pointCount - 1;
        Ov007PickerParams *params = p->params;
        if (func_ov007_020c25fc(path, x << 12, y << 12, params->minLen, params->maxLen,
                                params->minTurn) != 0) {
            int idx = last + 1;
            path->progressThresholds[idx] = progress;
            p->totalPoints++;
            func_ov007_020bfe4c((char *)p->camera, path->xCoords[idx], path->yCoords[idx],
                                -p->camera->distance, &p->pathPoints[idx]);
            ret = 1;
        }
    } else {
        ret = 2;
    }
    return ret;
}
