//cpp

extern "C" {
typedef int (*FP)(void *);
extern FP data_ov007_02103258;
void func_ov007_020c3e3c(int v) {
    data_ov007_02103258 = reinterpret_cast<FP>(v);
}
}
