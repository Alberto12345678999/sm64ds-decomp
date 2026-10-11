extern void _ZN6Player19func_ov002_020bd984Ej(char* c, unsigned int a);
void func_ov002_020d80d0(char* c){
  if (*(unsigned char*)(c+0x6f8) != 1) return;
  *(short*)(c+0x6be) = 0;
  *(unsigned char*)(c+0x6f8) = 0;
  *(unsigned char*)(c+0x6f4) = 0;
  *(unsigned char*)(c+0x714) = 0;
  _ZN6Player19func_ov002_020bd984Ej(c, 0x32);
}
