extern int WM_PowerOff(void *cb);
extern void func_02040388(void);
extern int data_020a0f94;

/* Power the wireless hardware off: WM_PowerOff sends WM command 6 (the
   SDK's WM_APIID_POWER_OFF, idle state only) with func_02040388 as the
   callback. A refusal sets the link status data_020a0f94 to 1 (error) and
   returns 0; otherwise 1. func_0203fcb0, func_0203fcec, func_0203fd28,
   func_0203fd64 and Wireless_Reset are the same wrapper on other
   commands. */
int func_0203fc74(void) {
    if (WM_PowerOff((void *)func_02040388) != 2) {
        data_020a0f94 = 1;
        return 0;
    }
    return 1;
}
