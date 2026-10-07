extern void func_0202ed14(char *o);
extern int _ZTV8dFader_c[];
extern int _ZTV15dFdBrightness_c[];
extern int _ZTV10dFdColor_c[];
extern void *data_020926f0;

void *func_0202fc40(char *self) {
    *(void**)self = &_ZTV8dFader_c;
    *(void**)self = &_ZTV15dFdBrightness_c;
    *(int*)(self + 4) = 0;
    *(int*)(self + 8) = 0;
    *(void**)self = &_ZTV10dFdColor_c;
    *(short*)(self + 0xc) = 0;
    *(void**)self = &data_020926f0;
    func_0202ed14(self);
    return self;
}
