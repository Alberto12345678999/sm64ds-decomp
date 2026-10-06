extern int _ZN15dExtFrameCtrl_c7AdvanceEv(void *p);

int func_ov002_020f65ec(char *c)
{
    void *p = *(void**)(c + 0x7c);
    if (p == 0)
        return (int)p;
    return _ZN15dExtFrameCtrl_c7AdvanceEv(p);
}
