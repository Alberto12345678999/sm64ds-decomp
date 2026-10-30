extern int OS_IsAlarmAvailable(void);
extern int OS_SetAlarm(void *a, void *b, void *c, void *d, int e);

/* OS_SetAlarm, but only once the alarm system is up
   (OS_IsAlarmAvailable); else 0. The watchdog alarm (func_0201a8b4,
   func_0201a96c) arms itself through it. */
int func_0201aa50(void *a, void *b, void *c, void *d, int e)
{
    int r = OS_IsAlarmAvailable();
    if (r == 0)
        return r;
    return OS_SetAlarm(a, b, c, d, e);
}
