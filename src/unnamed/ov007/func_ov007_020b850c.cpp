//cpp

namespace GX {
void LoadBGPltt(const void *, unsigned int, unsigned int);
}
namespace GXS {
void LoadBGPltt(const void *, unsigned int, unsigned int);
}

extern "C" {
extern int data_ov007_020d7a44[];
void func_ov007_020b850c(void) {
    GX::LoadBGPltt(data_ov007_020d7a44, 0x1f6, 0xa);
    GXS::LoadBGPltt(data_ov007_020d7a44, 0x1f6, 0xa);
}
}
