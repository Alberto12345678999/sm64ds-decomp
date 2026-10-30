/* The OS tick count in microseconds: ticks * 64 * 1000 / (HW_SYSTEM_CLOCK /
 * 1000). A tick is 64 system-clock cycles (OSi_TICK_TIMERCONTROL runs timer
 * 0 at prescaler 64), and HW_SYSTEM_CLOCK is the SDK's 33514000.
 * func_02059650 is the SDK's OS_GetTick. The quotient goes through _ll_udiv. */
typedef unsigned long long u64;

#define HW_SYSTEM_CLOCK 33514000

extern u64 func_02059650(void);

u64 func_02042784(void)
{
    return func_02059650() * 64000ULL / (HW_SYSTEM_CLOCK / 1000);
}
