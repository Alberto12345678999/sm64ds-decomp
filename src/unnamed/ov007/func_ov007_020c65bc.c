#include "types.h"
#include "Ov007StrokePath.h"
#include "Ov007Picker.h"

extern int func_ov007_020c25fc(Ov007StrokePath *path, int x, int y, int minLen, int maxLen,
                               int minTurn);
extern void func_ov007_020bfe4c(char *camera, int x, int y, int z, Vector3 *out);

/* The 0xd8-byte camera func_ov007_020c023c allocates; names as in
 * func_ov007_020c0128, only the slot this file reads. */
typedef struct Ov007Camera {
    char pad_00[0x2c];
    int distance; /* 0x2c */
} Ov007Camera;

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
