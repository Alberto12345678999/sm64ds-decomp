extern int func_ov007_020c3ce4(void);
extern void func_ov007_020c6724(void *self, int flag);
extern void *func_ov007_020c2b38(int count, const int *src1, const int *src2, const int *arg3);
extern void *func_ov007_020c2acc(int count, const unsigned char *a, const unsigned char *b,
                                 const int *x);
extern void func_ov007_020c6e68(void *self, int i);
extern int func_ov007_020c5db0(void *c);

struct C {
    char p8[8];
    int f8; // 0x8
    char p[8];
    int f14; // 0x14
    char p2[0x20];
    void **f38; // 0x38
};

void func_ov007_020c6784(void *object, int count, const int *pointCounts, const void *xCoords,
                         const void *yCoords, const int *const *progressThresholds, int mode) {
    struct C *self = (struct C *)object;
    int i;
    func_ov007_020c3ce4();
    func_ov007_020c6724(self, 1);
    /* Each mode interprets the coordinate-pointer tables in its own format. */
    for (i = 0; i < count; i++) {
        switch (mode) {
        case 0:
            self->f38[i] =
                func_ov007_020c2b38(pointCounts[i], ((const int *const *)xCoords)[i],
                                    ((const int *const *)yCoords)[i], progressThresholds[i]);
            break;
        case 1:
            self->f38[i] = func_ov007_020c2acc(
                pointCounts[i], ((const unsigned char *const *)xCoords)[i],
                ((const unsigned char *const *)yCoords)[i], progressThresholds[i]);
            break;
        }
        func_ov007_020c6e68(self, i);
    }
    self->f8 = count;
    self->f14 = func_ov007_020c5db0(self);
    func_ov007_020c3ce4();
}
