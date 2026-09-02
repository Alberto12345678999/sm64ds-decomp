// @symbol daObjWc_Obj05_c_classInit
extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN10dBgActor_cC2Ev(void *);
extern int _ZTV8CageLift[];
/* Reconstructed source-style name: SM64DS proves daObjWc_Obj05_c through RTTI,
 * allocation size, vtable identity, and the WC_OBJ05 registry profile; later
 * EAD lineage supplies classInit. Exact original spelling is not preserved.
 * The project's CageLift implementation aliases remain unchanged.
 * Historical alias: CageLift_Spawn. */
int *daObjWc_Obj05_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(816);
    if (p) { _ZN10dBgActor_cC2Ev(p); p[0] = (int)_ZTV8CageLift; }
    return p;
}
