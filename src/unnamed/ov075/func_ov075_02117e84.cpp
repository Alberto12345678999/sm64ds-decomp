//cpp
#include "dScEntry_c.h"

extern dScEntry_c::StepSet data_ov075_0211d870;

extern "C" {
extern void func_02020190(void);
extern u8 func_02020168(void);
extern void func_020200e0(void);
extern void func_02030994(void);
extern int func_0203d9b4(void);
extern int func_ov075_02116ce4(void *scene);
extern void func_02020124(void);

extern unsigned char data_0209fc58;
extern unsigned char data_0209d45c;
extern unsigned char data_02092778;

void func_ov075_02117e84(void *c) {
    dScEntry_c *scene = static_cast<dScEntry_c *>(c);
    if (data_0209fc58 != 0) {
        func_02020190();
        scene->HandlePlayerDisconnect(&data_ov075_0211d870);
        return;
    }
    if (func_02020168()) {
        func_02020190();
        func_020200e0();
        func_02030994();
        data_0209d45c = data_0209d45c & ~0xe;
        scene->mDisconnectHideMask = 0;
        scene->mRenderStep = 0;
        dScene_c::StartSceneFade(6, 2, 0);
        data_02092778 = 1;
        return;
    }
    if (func_0203d9b4() == 0)
        return;
    if (func_ov075_02116ce4(c) == 0)
        return;
    func_02020124();
}
}
