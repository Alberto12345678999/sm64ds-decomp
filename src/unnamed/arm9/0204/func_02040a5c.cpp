//cpp
#include "types.h"
#include "IRQ.h"

extern "C" {

typedef struct {
    char pad[0xb50];
    u32 field_b50;
} UnkStruct_020a3fc0;

extern UnkStruct_020a3fc0 data_020a3fc0;

/* Store val with bit 0 clear at +0xb50 of data_020a3fc0, under the IRQ
   lock. Its one caller, func_0203ea5c, declares it without arguments and
   calls it right after func_02040a84, with more than two players
   (data_02099e18), so r0 still holds that value. */
void func_02040a5c(u32 val)
{
    u32 saved = IRQ::Disable();
    data_020a3fc0.field_b50 = val & ~1u;
    IRQ::Restore(saved);
}
}
