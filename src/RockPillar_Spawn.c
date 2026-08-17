extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN8PlatformC2Ev(void *);
extern int _ZTV10RockPillar[];
int *RockPillar_Spawn(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(808);
    if (p) { _ZN8PlatformC2Ev(p); p[0] = (int)_ZTV10RockPillar; }
    return p;
}
