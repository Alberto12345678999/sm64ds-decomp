/* Reset the watchdog alarm's base to the current tick (layout and names:
 * func_0201aa18). */
typedef long long s64;
extern s64 OS_GetTick(void);

typedef struct WatchdogAlarm {
    char alarm[0x2c]; /* 0x00 -- OSAlarm */
    char pad_2c[4];
    s64 limit; /* 0x30 */
    s64 base;  /* 0x38 */
} WatchdogAlarm;

void func_0201a9fc(char *c) {
    ((WatchdogAlarm *)c)->base = OS_GetTick();
}
