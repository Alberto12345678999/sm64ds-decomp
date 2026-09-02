extern void *_ZN7fBase_cnwEj(unsigned);
extern void _ZN10dBgActor_cC2Ev(void *);
extern int _ZTV16daObjBC_Switch_c[];
// @symbol daObjBC_Switch_c_classInit
/* Reconstructed source-style name: SM64DS proves daObjBC_Switch_c through
 * RTTI, allocation size, vtable identity, and the BC_SWITCH registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. The project's daObjBC_Switch_c implementation aliases remain
 * unchanged. Historical alias: daObjBC_Switch_c_Spawn. */
int *daObjBC_Switch_c_classInit(void)
{
    int *p = (int *)_ZN7fBase_cnwEj(816);
    if (p) { _ZN10dBgActor_cC2Ev(p); p[0] = (int)_ZTV16daObjBC_Switch_c; }
    return p;
}
