extern void func_02017acc();
extern void func_020731dc();
extern void _ZN13SharedFilePtr9ConstructEj();
extern struct SharedFilePtr data_ov081_02128d60;
extern int func_02017ab4();
extern void data_ov081_02128d7c[];
extern struct SharedFilePtr data_ov081_02128d68;
extern int SharedFilePtr_Destruct_Anim();
extern void data_ov081_02128d70[];
void __sinit_ov081_021280e8(void)
{
    func_02017acc(data_ov081_02128d60, 813);
    func_020731dc(data_ov081_02128d60, func_02017ab4, data_ov081_02128d7c);
    _ZN13SharedFilePtr9ConstructEj(data_ov081_02128d68, 814);
    func_020731dc(data_ov081_02128d68, SharedFilePtr_Destruct_Anim, data_ov081_02128d70);
}
