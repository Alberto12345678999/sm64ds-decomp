//cpp
#include "dScEntry_c.h"

extern dScEntry_c::StepSet data_ov075_0211d780;

extern "C" {
extern int func_02020168(void);
extern void func_02020304(void);
extern void func_020200e0(void);
extern int func_0203d9b4(void);
extern int func_ov075_02116d40(void*);
extern int func_02020124(void);
void func_ov075_02116e44(char *c) {
    if(func_02020168()){
        func_02020304();
        func_020200e0();
        *(short*)0x4000050 = 0;
        reinterpret_cast<dScEntry_c *>(c)->ChangeStepsAfterDelay(&data_ov075_0211d780, 5);
        return;
    }
    int a = func_0203d9b4();
    if (a == 0)
        return;
    int b = func_ov075_02116d40(c);
    if (b == 0)
        return;
    func_02020124();
}
}
