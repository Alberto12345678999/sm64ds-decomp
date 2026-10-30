//cpp
#include "types.h"
#include "IRQ.h"

extern "C" {

/* NitroSDK CARDRomRegion. */
typedef struct CARDRomRegion {
    u32 offset;
    u32 length;
} CARDRomRegion;

extern CARDRomRegion data_020a8064; /* fsi_ovt9 */
extern CARDRomRegion data_020a806c; /* fsi_ovt7 */
extern char data_0209a7d8[];

u32 func_0205e904(u32 newVal);
int FSi_CompareDigest(char *spec_digest, void *src, int len);
void Crash(void);

void func_0205db88(int target, void *ptr, u32 size) {
    CARDRomRegion *pr;
    if (target == 0) {
        pr = &data_020a8064;
    } else {
        pr = &data_020a806c;
    }
    if (ptr != 0 && target == 0) {
        u32 r4 = func_0205e904(1);
        if (!FSi_CompareDigest(data_0209a7d8, ptr, size)) {
            Crash();
        }
        func_0205e904(r4);
    }
    u32 irqState = IRQ::Disable();
    pr->offset = (u32)ptr;
    pr->length = size;
    IRQ::Restore(irqState);
}
}
