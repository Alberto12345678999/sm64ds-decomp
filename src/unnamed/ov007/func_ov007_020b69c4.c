#include "types.h"
extern u8 *data_ov007_0210342c;

/* data_ov007_0210342c: the overlay's manager; names as in
 * func_ov007_020ada70, func_ov007_020b0da0 and func_ov007_020b2370, only the
 * slots this file touches. Left raw: the 0/1 pair at +0xec/+0xf0, the two
 * bytes at +0xfc and the three func_ov007_020c946c records at +0x44..+0x4f
 * (no reader names them). */
typedef struct Ov007Work {
    char pad_00[0x40];
    /* 0x40: func_ov007_020bce70 requests palette n on it and blends over its
     * stateTicks */
    struct Ov007MenuState *paletteState;
    char pad_44[0xb0];
    struct Ov007Model *model; /* 0xf4: func_ov007_020b2bd4 builds it */
    char pad_f8[8];
    struct Ov007Figure *figure;    /* 0x100: func_ov007_020beaa0 */
    struct Ov007Figure *altFigure; /* 0x104: func_ov007_020be850 returns it when +0xec is 1 */
} Ov007Work;

typedef char Ov007Work_size_must_be_0x108[sizeof(Ov007Work) == 0x108 ? 1 : -1];

/* The extern keeps the tree's u8 * spelling; the typed view is reached
 * through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

extern void *func_ov007_020c9388(int initialState);
extern void *func_ov007_020c946c(void *r5);

#pragma opt_strength_reduction off
void func_ov007_020b69c4(void)
{
    int i;
    int arg;

    WORK->model = 0;
    WORK->figure = 0;
    WORK->altFigure = 0;
    *(int *)(data_ov007_0210342c + 0xf0) = 0;
    *(int *)(data_ov007_0210342c + 0xec) = *(int *)(data_ov007_0210342c + 0xf0);

    i = 0;
    do {
        (data_ov007_0210342c + i)[0xfc] = (u8)0;
        i++;
    } while (i < 2);

    WORK->paletteState = (struct Ov007MenuState *)func_ov007_020c9388(0);

    arg = 0;
    i = 0;
    do {
        *(void **)(data_ov007_0210342c + (i << 2) + 0x44) = func_ov007_020c946c((void *)arg);
        i++;
    } while (i < 3);

    *(int **)(*(int ***)(data_ov007_0210342c + 0x44)) =
        (int *)((char *)*(int **)(data_ov007_0210342c + 0x4c) + 4);
    *(int **)(*(int ***)(data_ov007_0210342c + 0x48)) =
        (int *)((char *)*(int **)(data_ov007_0210342c + 0x44) + 4);
}
