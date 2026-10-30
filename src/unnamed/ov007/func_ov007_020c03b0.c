#include "Ov007BgLayer.h"

typedef volatile unsigned short vu16;

/* Per BG, its bit in Ov007BgList.mask. */
extern int data_ov007_020d7d6c[];
extern void func_ov007_020c076c(Ov007BgLayer *layer, int engines);

/* Shows the list's layers on its engines: for each BG, the first listed
 * layer with a valid BG and priority that is visible and in the mask is
 * uploaded (func_ov007_020c076c) and its priority written into BGnCNT. */
void func_ov007_020c03b0(Ov007BgList *list) {
    Ov007BgLayer *volatile layers[4];
    int shown[4];
    Ov007BgLayer *volatile *pa;
    int *pb;
    Ov007BgLayer *node;
    int mask;
    int bg, pri;
    int toMain, toSub;
    int engines;

    /* layers is stored but never read. Both arrays are cleared through
     * pointers; direct stores do not match. */
    pa = (Ov007BgLayer *volatile *)(layers);
    pa[0] = 0;
    pa[1] = 0;
    pa[2] = 0;
    pa[3] = 0;
    pb = (int *)(shown);
    pb[0] = 0;
    pb[1] = 0;
    pb[2] = 0;
    pb[3] = 0;

    engines = list->engines;
    node = list->head;
    mask = list->mask;
    toMain = engines & 1;
    toSub = engines & 2;
    if (node == 0)
        return;

    do {
        bg = node->bg;
        pri = node->priority;
        if (bg >= 0 && bg <= 3 && pri >= 0 && pri <= 3 && shown[bg] == 0) {
            layers[bg] = node;
            if (node->visible == 1 && (mask & data_ov007_020d7d6c[bg]) != 0) {
                func_ov007_020c076c(node, list->engines);
                if (toMain) {
                    switch (bg) {
                    case 0:
                        *(vu16 *)0x4000008 = (*(vu16 *)0x4000008 & ~3) | pri;
                        break;
                    case 1:
                        *(vu16 *)0x400000a = (*(vu16 *)0x400000a & ~3) | pri;
                        break;
                    case 2:
                        *(vu16 *)0x400000c = (*(vu16 *)0x400000c & ~3) | pri;
                        break;
                    case 3:
                        *(vu16 *)0x400000e = (*(vu16 *)0x400000e & ~3) | pri;
                        break;
                    }
                }
                if (toSub) {
                    switch (bg) {
                    case 0:
                        *(vu16 *)0x4001008 = (*(vu16 *)0x4001008 & ~3) | pri;
                        break;
                    case 1:
                        *(vu16 *)0x400100a = (*(vu16 *)0x400100a & ~3) | pri;
                        break;
                    case 2:
                        *(vu16 *)0x400100c = (*(vu16 *)0x400100c & ~3) | pri;
                        break;
                    case 3:
                        *(vu16 *)0x400100e = (*(vu16 *)0x400100e & ~3) | pri;
                        break;
                    }
                }
                shown[bg] = 1;
            }
        }
        node = node->next;
    } while (node != 0);
}
