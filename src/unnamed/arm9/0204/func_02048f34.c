#include "types.h"

typedef struct {
    int a, b;
} Elem;

// Copies pair i (i in 0..8) from table data_020821c0 into
// data_02099fa8 / data_02099fac.
extern u32 data_020821c0[];
extern volatile u32 data_02099fa8;
extern volatile u32 data_02099fac;
extern void func_0204f94c(void *p);
extern int *data_020a4bec;
extern Elem data_020a4c18[];
extern Elem data_020a4c08[];
extern Elem data_020a4bf8[];
extern Elem data_020a4bf0;

void func_02048fd4(int i) {
    volatile u32 *tbl;
    int j;
    if (i < 0)
        return;
    if (i > 8)
        return;
    tbl = data_020821c0;
    j = i * 2;
    data_02099fa8 = tbl[j];
    j++;
    data_02099fac = tbl[j];
}

void func_02048f34(int *owner) {
    int i;
    data_020a4bec = owner;
    for (i = 0; i < 6; i++)
        func_0204f94c(&data_020a4c18[i]);
    for (i = 0; i < 2; i++)
        func_0204f94c(&data_020a4c08[i]);
    for (i = 0; i < 2; i++)
        func_0204f94c(&data_020a4bf8[i]);
    func_0204f94c(&data_020a4bf0);
    func_02048fd4(0);
}
