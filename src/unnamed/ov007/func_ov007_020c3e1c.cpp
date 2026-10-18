//cpp

extern "C" {
typedef int (*FP)(void);
extern FP data_ov007_02104c14;
void func_ov007_020c3e1c(int v) {
    data_ov007_02104c14 = reinterpret_cast<FP>(v);
}
}
