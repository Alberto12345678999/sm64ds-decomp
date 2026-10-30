extern void *func_0201aab0(void *alarm);
/* The watchdog alarm's destructor, which __sinit_02074e0c registers:
   cancel it (func_0201aab0) and return it. */
void *func_0201aaec(void *alarm) {
    func_0201aab0(alarm);
    return alarm;
}
