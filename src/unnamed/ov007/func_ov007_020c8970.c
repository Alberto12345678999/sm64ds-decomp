// Long-branch veneer. #pragma long_calls makes mwccarm emit the pooled
// `ldr ip,[pc]; bx ip` absolute tail-call the ROM uses to reach the target.
#include "Ov007Transition.h"

#pragma long_calls on
extern void func_ov007_020c897c(Ov007Transition *tr);

void func_ov007_020c8970(Ov007Transition *tr) {
    func_ov007_020c897c(tr);
}
