//cpp
#include "types.h"
#include "IRQ.h"

extern "C" {

/* The watchdog alarm at data_0209d574; layout and names are func_0201aa18's.
 */
typedef struct {
    char alarm[0x2c]; /* 0x00 -- OSAlarm */
    char pad_2c[4];
    u64 limit;      /* 0x30 */
    char base[0x8]; /* 0x38 -- u64 tick, reset by func_0201a9fc */
    u8 suspended;   /* 0x40 */
} Struct_0201a96c;

typedef void (*OSAlarmHandler)(void *);
extern void func_0201aa50(void *, long long, OSAlarmHandler, void *);
extern void func_0201aaa4(void *);

extern void func_0201a8b4(void *);

/* Set the suspended flag and return the old one. Clearing it re-arms the
   alarm for the full limit with func_0201a8b4 as the handler; setting it
   cancels the alarm through func_0201aaa4. */
u8 func_0201a96c(Struct_0201a96c *self, u8 newVal)
{
    u32 saved = IRQ::Disable();
    u8 oldVal = self->suspended;
    self->suspended = newVal;

    if (oldVal != 0 && newVal == 0) {
        func_0201aa50(self, self->limit, func_0201a8b4, self);
    } else if (oldVal == 0 && newVal != 0) {
        func_0201aaa4(self);
    }

    IRQ::Restore(saved);
    return oldVal;
}
}
