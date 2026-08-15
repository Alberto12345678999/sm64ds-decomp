extern void func_0202ed14(char *o);
extern void *_ZTV8dFader_c;
extern void *_ZTV15dFdBrightness_c;
extern void *_ZTV10dFdColor_c;
extern void *_ZTV7dWipe_c;

void *func_0202fc40(char *self) {
    *(void**)self = &_ZTV8dFader_c;
    *(void**)self = &_ZTV15dFdBrightness_c;
    *(int*)(self + 4) = 0;
    *(int*)(self + 8) = 0;
    *(void**)self = &_ZTV10dFdColor_c;
    *(short*)(self + 0xc) = 0;
    *(void**)self = &_ZTV7dWipe_c;
    func_0202ed14(self);
    return self;
}
