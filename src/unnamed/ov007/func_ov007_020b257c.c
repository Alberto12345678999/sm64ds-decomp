#include "Ov007Work.h"
#include "Ov007Model.h"
#include "Ov007Figure.h"

extern char* data_ov007_0210342c;

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
