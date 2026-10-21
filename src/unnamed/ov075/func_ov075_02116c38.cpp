//cpp
#include "dScEntry_c.h"

extern dScEntry_c::StepSet data_ov075_0211d780;
extern dScEntry_c::StepSet data_ov075_0211d828;

extern "C" {
extern int data_0209fc68[];

void func_ov075_02116c38(void *c) {
    if (*data_0209fc68) {
        reinterpret_cast<dScEntry_c *>(c)->ChangeStepsAfterDelay(&data_ov075_0211d828, 0x14);
    } else {
        reinterpret_cast<dScEntry_c *>(c)->ChangeStepsAfterDelay(&data_ov075_0211d780, 0x14);
    }
}
}
