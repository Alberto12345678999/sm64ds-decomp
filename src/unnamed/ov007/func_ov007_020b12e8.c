#include "types.h"
#include "Ov007Work.h"
#include "Ov007Settings.h"

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

extern void func_ov007_020b1390(int mode);
extern void func_ov007_020b7eec(Ov007BootArgs *bootArgs);

void func_ov007_020b12e8(void) {
    func_ov007_020b1390(0);
    func_ov007_020b7eec(WORK->settings->bootArgs);
}
