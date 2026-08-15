extern void func_ov006_020c4048(void *);
extern void _ZN9ModelAnimC1Ev(void *);
extern int _ZTV16dMgJump3DMario_c[];
int *func_ov006_020c8a04(int *t)
{
    func_ov006_020c4048(t);
    t[0] = (int)_ZTV16dMgJump3DMario_c;
    _ZN9ModelAnimC1Ev((char *)t + 0x4c);
    return t;
}
