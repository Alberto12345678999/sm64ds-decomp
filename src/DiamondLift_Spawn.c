// @symbol daObjKm1_Ukishima_c_classInit
extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN10dBgActor_cC2Ev(void *);
extern int _ZTV11DiamondLift[];
/* Reconstructed source-style name: SM64DS proves daObjKm1_Ukishima_c through
 * RTTI, allocation size, vtable identity, and the KM1_UKISHIMA registry
 * profile; later EAD lineage supplies classInit. Exact original spelling is
 * not preserved. The project's DiamondLift implementation alias remains
 * unchanged. Historical alias: DiamondLift_Spawn. */
int *daObjKm1_Ukishima_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(800);
    if (p) { _ZN10dBgActor_cC2Ev(p); p[0] = (int)_ZTV11DiamondLift; }
    return p;
}
