struct Obj {
    void *vt;          /* 0x0 */
    char pad[2];       /* 0x4 */
    short f6;          /* 0x6 */
    short f8;          /* 0x8 */
};

extern void func_020226a4(char *p);
extern int _ZTVN5dPa_c7level_c15scaleCallback_cE;

struct Obj *func_020225fc(struct Obj *thiz)
{
    func_020226a4((char *)thiz);
    thiz->vt = &_ZTVN5dPa_c7level_c15scaleCallback_cE;
    thiz->f6 = 0x1000;
    thiz->f8 = 0;
    return thiz;
}
