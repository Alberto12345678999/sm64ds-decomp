struct S;

extern int ReadUnalignedSignedInt(unsigned char *p);

int func_02008008(struct S *p, int v)
{
    int r0 = ReadUnalignedSignedInt((unsigned char *)v);
    *(int *)((char *)p + 0x170) = r0;
    return 1;
}
