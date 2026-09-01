extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN8dActor_cC2Ev(void *);
extern int _ZTV12daSoundObj_c[];
int *daSoundObj_c_Spawn(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(228);
    if (p) { _ZN8dActor_cC2Ev(p); p[0] = (int)_ZTV12daSoundObj_c; }
    return p;
}
