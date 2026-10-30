extern void func_02040014(void);
extern int WM_StartParent(void *p);

/* Start as parent: WM_StartParent sends WM command 8 (the SDK's
   WM_APIID_START_PARENT) with func_02040014 as the callback. 1 when the
   request is accepted (2). */
int func_0203fb98(void) {
    return WM_StartParent((void *)func_02040014) == 2;
}
