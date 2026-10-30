#include "Ov007Work.h"
#include "Ov007Model.h"
#include "Ov007Figure.h"

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
