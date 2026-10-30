extern void func_02040014(void);
extern int func_02061fdc(void *p);

/* Start as parent: func_02061fdc sends WM command 8 (the SDK's
   WM_APIID_START_PARENT) with func_02040014 as the callback. 1 when the
   request is accepted (2). */
int func_0203fb98(void) {
    return func_02061fdc((void *)func_02040014) == 2;
}
