#include "Ov007Work.h"
#include "Ov007Model.h"

extern char* data_ov007_0210342c;

/* The 0x1c-byte record func_ov007_020beaa0 builds around an Ov007Model;
 * names as in func_ov007_020b0da0, medium-confidence. */
typedef struct Ov007Figure {
    char pad_00[4];
    Ov007Model *model; /* 0x04: func_ov007_020bc6d4 */
} Ov007Figure;

#define WORK ((Ov007Work*)data_ov007_0210342c)

/* Holds the manager model's three animation players where they are playing,
 * and stops both figures' bone animations (state 2). */
void func_ov007_020b257c(void) {
    int* p;
    p = &WORK->model->boneAnim->state;
    if (*p == 0) *p = 1;
    p = &WORK->model->texSrtAnim->state;
    if (*p == 0) *p = 1;
    p = &WORK->model->texSeqAnim->state;
    if (*p == 0) *p = 1;
    WORK->figure->model->boneAnim->state = 2;
    WORK->altFigure->model->boneAnim->state = 2;
}
