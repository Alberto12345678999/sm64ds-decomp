#include "types.h"
#include "Ov007Work.h"
#include "Ov007Settings.h"

extern void func_ov007_020b1390(int mode);
extern void func_ov007_020b7eec(Ov007BootArgs *bootArgs);

void func_ov007_020b12e8(void) {
    func_ov007_020b1390(0);
    func_ov007_020b7eec(WORK->settings->bootArgs);
}
