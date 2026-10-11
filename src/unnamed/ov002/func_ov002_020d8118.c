extern void _ZN6Player19func_ov002_020bda48Ev(char* c);
extern void _ZN6Player19func_ov002_020bd9ecEj(char* c, unsigned int v);
extern void _ZN6Player19func_ov002_020c43c4Ej(char* c, int v);

void func_ov002_020d8118(char* c)
{
    _ZN6Player19func_ov002_020bda48Ev(c);
    *(short*)(c + 0x600 + 0xbe) = 0x258;
    _ZN6Player19func_ov002_020bd9ecEj(c, 0x32);
    _ZN6Player19func_ov002_020c43c4Ej(c, 5);
    *(unsigned char*)(c + 0x6f8) = 1;
}
