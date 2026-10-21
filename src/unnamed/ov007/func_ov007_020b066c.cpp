//cpp
#include "Ov007MenuState.h"

extern "C" {
extern void func_ov007_020b283c(void);
extern void func_ov007_020b9770(void);
extern void func_ov007_020bf304(void);
extern void func_ov007_020b6544(void);
extern void func_ov007_020bcba8(int i);
extern void func_ov007_020bca40(int i);
extern void RequestScreenFade(int a, int b, int c);
extern void func_ov007_020bd1c0(int i);
extern void func_ov007_020b131c(void);
extern char *data_ov007_0210342c;
}

typedef int (*FP)(int);
#define G  (data_ov007_0210342c)

/* The 0xa0-byte model record func_ov007_020bc6d4 allocates; names as in
 * func_ov007_020bc47c, only the slot this file writes. */
struct Ov007Model {
    char pad_00[0x94];
    int visible; /* 0x94: func_ov007_020bbff0 renders only while it is nonzero */
};

/* The 0x1c-byte record func_ov007_020beaa0 builds around an Ov007Model;
 * names as in func_ov007_020b0da0. */
struct Ov007Figure {
    char pad_00[4];
    Ov007Model *model; /* 0x04: func_ov007_020bc6d4 */
};

/* The 0x3c-byte record func_ov007_020b6a84 allocates; names as in
 * func_ov007_020aec94. +0x37/+0x38 (the bytes the +0x2c callback returns for
 * queries 0x14/0x15 here) and the record its first word points at stay raw. */
struct Ov007Settings {
    char pad_00[0x39];
    /* 0x39: func_ov007_020b7d94's kind, the window menu state 9 opens before
     * the choice goes through (func_ov007_020b0834); cleared here */
    unsigned char dialogKind;
};

/* data_ov007_0210342c: the overlay's manager; names as in
 * func_ov007_020aec94, func_ov007_020b0da0 and func_ov007_020c0078, only the
 * slots this file touches. The callback at +0x2c and the 0/1 pair at
 * +0xec/+0xf0 stay raw on G. */
struct Ov007Work {
    char pad_00[4];
    Ov007MenuState *states[3]; /* 0x04: func_ov007_020c9388 */
    char pad_10[0x18];
    Ov007Settings *settings; /* 0x28: func_ov007_020b6a84 */
    char pad_2c[0xc8];
    Ov007Model *model; /* 0xf4: func_ov007_020b2bd4 builds it */
    char pad_f8[8];
    Ov007Figure *figure;    /* 0x100: func_ov007_020beaa0 */
    Ov007Figure *altFigure; /* 0x104: func_ov007_020be850 returns it when +0xec is 1 */
};

typedef char Ov007Model_visible_must_be_at_0x94[(int)&((Ov007Model *)0)->visible == 0x94 ? 1 : -1];
typedef char Ov007Work_size_must_be_0x108[sizeof(Ov007Work) == 0x108 ? 1 : -1];

/* The extern keeps the tree's char * spelling; the typed view is reached
 * through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

extern "C" void func_ov007_020b066c(void)
{
    switch (WORK->states[0]->previousState) {
    case 6:
        func_ov007_020b283c();
        break;
    case 4:
        func_ov007_020b9770();
        break;
    case 5:
        func_ov007_020bf304();
        (*(FP*)(G + 0x2c))(0x11);
        break;
    default:
        *((unsigned char *)WORK->settings + 0x38) = (unsigned char)(*(FP *)(G + 0x2c))(0x15);
        *((unsigned char *)WORK->settings + 0x37) = (unsigned char)(*(FP *)(G + 0x2c))(0x14);
        WORK->settings->dialogKind = 0;
        break;
    }

    func_ov007_020b6544();
    func_ov007_020bcba8(1);
    func_ov007_020bca40(0);

    {
        Ov007Work *bb = WORK;
        if ((unsigned short)(short)(bb->states[0]->previousState - 4) <= 2) {
            bb->states[1]->requestedState = 5;
        } else {
            switch (*(int *)(*(char **)bb->settings + 4)) {
            case 0:
            case 2:
                bb->states[1]->requestedState = 0xb;
                break;
            case 1:
                bb->states[1]->requestedState = 0xa;
                RequestScreenFade(3, 0xa, 0);
                break;
            }
        }
    }

    WORK->states[2]->requestedState = 0;

    *(int*)(G + 0xec) = *(int*)(G + 0xf0);

    if (*(int*)(G + 0xf0) == 0)
        *(int*)(G + 0xf0) = 1;
    else
        *(int*)(G + 0xf0) = 0;

    func_ov007_020bd1c0(0);

    WORK->model->visible = 0;
    WORK->figure->model->visible = 0;
    WORK->altFigure->model->visible = 0;
    func_ov007_020b131c();
}
