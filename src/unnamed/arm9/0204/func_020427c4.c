/* The OS tick count in milliseconds: ticks * 64 / (HW_SYSTEM_CLOCK / 1000).
 * A tick is 64 system-clock cycles (OSi_TICK_TIMERCONTROL runs timer 0 at
 * prescaler 64). pret's pokediamond spells the same expression in
 * Timer3CountToMilliSeconds. ShowCrashScreen hands the result to nds_printt
 * with the time template "99h59m59s999".
 * func_02059650 is OS_GetTick. The quotient goes through _ll_udiv. */
typedef unsigned long long u64;

#define HW_SYSTEM_CLOCK 33514000

extern u64 func_02059650(void);

u64 func_020427c4(void) {
    return func_02059650() * 64ULL / (HW_SYSTEM_CLOCK / 1000);
}
