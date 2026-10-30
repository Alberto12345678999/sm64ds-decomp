#include "Ov007Work.h"
#include "Ov007Model.h"

extern void func_ov007_020bc374(Ov007Model *m, int i, int startFrame, int fadeFrames);
extern void func_ov007_020bc3dc(Ov007Model *m, int i, int startFrame, int d);
extern void func_ov007_020bc2e4(Ov007Model *m, int i, int startFrame);
extern void func_ov007_020bc32c(Ov007Model *m, int i, int startFrame);
extern void func_ov007_020be980(struct Ov007Figure *fig, int anim, int a2);
extern int func_ov007_020be964(struct Ov007Figure *fig);

void func_ov007_020b2614(int self, int b, int c) {
    if (c > 0) {
        func_ov007_020bc374(WORK->model, self, b, c);
    } else {
        func_ov007_020bc3dc(WORK->model, self, b, c);
        WORK->model->visible = 1;
        WORK->model->animTick = 1;
    }
    func_ov007_020bc2e4(WORK->model, self, b);
    func_ov007_020bc32c(WORK->model, self, b);
    if (self == 0) {
        func_ov007_020be980(WORK->figure, 0, b);
        func_ov007_020be980(WORK->altFigure, 0, b);
    } else {
        func_ov007_020be964(WORK->figure);
        func_ov007_020be964(WORK->altFigure);
    }
}
