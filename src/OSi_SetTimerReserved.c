/* OSi_SetTimerReserved (the Nitro SDK's os_timer.c): mark a hardware timer
 * as taken by the OS. OS_InitTick reserves timer 0 and OS_InitAlarm timer 1. */
extern unsigned short data_020a642c; /* OSi_TimerReserved */

void OSi_SetTimerReserved(int timerNum) {
    data_020a642c |= (1 << timerNum);
}
