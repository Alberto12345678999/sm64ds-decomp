/* 1 if two 6-byte MAC addresses (three halfwords each) are equal, else 0.
   The parent's WM_StartParent callback (func_02040014) admits a child
   with it, and func_0203ea5c matches addresses with it. */
int func_02042748(unsigned short *a, unsigned short *b)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}
