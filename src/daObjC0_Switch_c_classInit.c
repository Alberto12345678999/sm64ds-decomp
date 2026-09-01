// @symbol daObjC0_Switch_c_classInit
extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN10dBgActor_cC2Ev(void *);
extern int _ZTV12SwitchPillar[];
/* Reconstructed source-style name: SM64DS proves daObjC0_Switch_c through
 * RTTI, allocation size, vtable identity, and the C0_SWITCH registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. Historical alias: SwitchPillar_Spawn. */
int *daObjC0_Switch_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(800);
    if (p) { _ZN10dBgActor_cC2Ev(p); p[0] = (int)_ZTV12SwitchPillar; }
    return p;
}
