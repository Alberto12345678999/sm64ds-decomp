extern int OS_IsAlarmAvailable(void);
extern int OS_SetAlarm(void *a, void *b, void *c, void *d, int e);

int func_0201aa50(void *a, void *b, void *c, void *d, int e)
{
    int r = OS_IsAlarmAvailable();
    if (r == 0)
        return r;
    return OS_SetAlarm(a, b, c, d, e);
}
