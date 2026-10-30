//cpp
#include "types.h"
#include "IRQ.h"

extern "C" {

/* The watchdog alarm at data_0209d574; layout and names are func_0201aa18's.
   This function hands the limit on as its two halves. */
typedef struct {
    char alarm[0x2c]; /* 0x00 -- OSAlarm */
    char pad_2c[4];
    u32 limitLo;    /* 0x30 */
    u32 limitHi;    /* 0x34 */
    char base[0x8]; /* 0x38 -- u64 tick, reset by func_0201a9fc */
    u8 suspended;   /* 0x40 */
} Struct_0201a96c;

extern void func_0201aa50(Struct_0201a96c *self, u32 a, u32 b, void *funcPtr, Struct_0201a96c *ctx);
extern void func_0201aaa4(Struct_0201a96c *self);

extern void func_0201a8b4(void);

/* Set the suspended flag and return the old one. Clearing it re-arms the
   alarm for the full limit with func_0201a8b4 as the handler; setting it
   cancels the alarm through func_0201aaa4.

   The ROM symbol stays func_0201a96c. This definition uses another name so
   the object does not define that symbol: rombuild would otherwise isolate
   the TU down to the one function and drop the static initializer. The link
   aliases func_0201a96c onto this body. */
static u8 func_0201a96c_body(Struct_0201a96c *self, u8 newVal) {
    u32 saved = IRQ::Disable();
    u8 oldVal = self->suspended;
    self->suspended = newVal;

    if (oldVal != 0 && newVal == 0) {
        func_0201aa50(self, self->limitLo, self->limitHi, func_0201a8b4, self);
    } else if (oldVal == 0 && newVal != 0) {
        func_0201aaa4(self);
    }

    IRQ::Restore(saved);
    return oldVal;
}
}

/* File-scope watchdog. mwcc emits __sinit_func_0201a96c.cpp: it calls
   func_0201aa18, then registers func_0201aaec through the compiler node
   at 0x0209d528. The 32 shorts at data_0209d534 sit between that node and
   the alarm, so they are part of this TU's one .bss run.

   mwcc names that node from how many named parameters this TU has already
   seen. Thirty-three here move it off @58, which ov002 already owns, onto
   @91. The declaration is not called. */
extern "C" void *func_0201aa18(char *c);
extern "C" void wdog_node_number(int n01, int n02, int n03, int n04, int n05, int n06, int n07,
                                 int n08, int n09, int n10, int n11, int n12, int n13, int n14,
                                 int n15, int n16, int n17, int n18, int n19, int n20, int n21,
                                 int n22, int n23, int n24, int n25, int n26, int n27, int n28,
                                 int n29, int n30, int n31, int n32, int n33);

struct WatchdogAlarm {
    unsigned char raw[0x44];

    WatchdogAlarm() {
        func_0201aa18((char *)this);
    }
    ~WatchdogAlarm();
};

unsigned short data_0209d534[32];
WatchdogAlarm data_0209d574;
