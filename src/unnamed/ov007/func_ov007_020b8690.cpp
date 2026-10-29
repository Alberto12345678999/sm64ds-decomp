//cpp

extern "C" {
// Clears two ov007 state globals, runs func_ov007_020c94e4, then releases
// two cached handles via func_ov007_020c44c4 (zeroing each afterwards).
extern int data_ov007_0210345c;
extern short data_ov007_02103458;
extern char *data_ov007_0210346c;
extern char *data_ov007_02103460;
extern void func_ov007_020c94e4(void);
extern int func_ov007_020c44c4(char *p);

void func_ov007_020b8690(void) {
    // The guard folds away, but it keeps pa and pb alive through
    // propagation, so both addresses load before the zero (ROM: zero in r0,
    // pb in r1, pa in r2). notes/mwccarm-codegen.md 6dh.
    int *pa = &data_ov007_0210345c;
    short *pb = &data_ov007_02103458;
    if (pa != 0 && pb != 0) {
        *pa = 0;
        *pb = 0;
    }
    func_ov007_020c94e4();
    if (data_ov007_0210346c != 0) {
        func_ov007_020c44c4(data_ov007_0210346c);
        data_ov007_0210346c = 0;
    }
    if (data_ov007_02103460 != 0) {
        func_ov007_020c44c4(data_ov007_02103460);
        data_ov007_02103460 = 0;
    }
}
}
