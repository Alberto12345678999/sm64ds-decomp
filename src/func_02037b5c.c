void func_02037b1c(char* c);
void _ZN5dBgPi5ResetEv(char* c);

void func_02037b5c(char* c)
{
    unsigned char* f;
    func_02037b1c(c);
    f = (unsigned char*)(((int)c + 0x70));
    *f &= ~1;
    *f &= ~4;
    *f &= ~8;
    *f &= ~0x10;
    *f &= ~2;
    *f &= ~0x20;
    *f &= ~0x40;
    _ZN5dBgPi5ResetEv(c + 0x10);
    _ZN5dBgPi5ResetEv(c + 0x74);
    _ZN5dBgPi5ResetEv(c + 0x9c);
    _ZN5dBgPi5ResetEv(c + 0xc4);
    *(int*)(c + 0xfc) = 0;
    *(int*)(c + 0x100) = -0x1000;
    *(int*)(c + 0x104) = 0;
}
