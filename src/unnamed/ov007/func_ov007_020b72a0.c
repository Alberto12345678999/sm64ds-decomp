#include "Ov007Work.h"

extern int func_ov007_020b7384(void *display);
extern int func_ov007_020b7364(void *display);
extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* The display hook func_ov007_020b6eb4 calls: func_ov007_020b7384 loads the
 * display record's two OAM buffers and func_ov007_020b7364 uploads its main
 * and sub BG layer lists. */
void func_ov007_020b72a0(void) {
    func_ov007_020b7384(WORK->display);
    func_ov007_020b7364(WORK->display);
}
