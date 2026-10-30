#include "Ov007Work.h"

/* The model record func_ov007_020bc6d4 builds; names as in
 * func_ov007_020be9ac and func_ov007_020bc7dc, only the slots this file
 * writes. */
typedef struct Ov007Model {
    char pad_00[0x94];
    int visible;  /* 0x94: func_ov007_020bbff0 renders only while it is nonzero */
    int animTick; /* 0x98: 1 on the frames that step the animations */
} Ov007Model;

typedef char
    Ov007Model_animTick_must_be_at_0x98[(int)&((Ov007Model *)0)->animTick == 0x98 ? 1 : -1];

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

extern void func_ov007_020bc374(char* self, int b, int c, int d);
extern void func_ov007_020bc3dc(char* self, int b, int c, int d);
extern void func_ov007_020bc2e4(void* c, int i, int a2);
extern void func_ov007_020bc32c(void* c, int i, int a2);
extern void func_ov007_020be980(void* p, int i, int a2);
extern void func_ov007_020be964(void* p);

void func_ov007_020b2614(int self, int b, int c) {
    if (c > 0) {
        func_ov007_020bc374((char *)WORK->model, self, b, c);
    } else {
        func_ov007_020bc3dc((char *)WORK->model, self, b, c);
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
