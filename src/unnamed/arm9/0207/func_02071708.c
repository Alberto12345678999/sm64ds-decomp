/* Count the trailing zero bits of w0, 32 for 0: skip whole zero bytes from
   the low end, then count the low set bits of the complemented byte.
   __num2dec_internal uses it as MSL's __count_trailing_zero
   to strip the significand's low zeros. The variadic signature keeps w0 in
   memory for the byte walk. */
int func_02071708(int w0, ...)
{
    unsigned char *p;
    int count;
    unsigned int c;
    if (w0 != 0) {
        p = (unsigned char *)&w0;
        count = 0;
        c = *p;
        if (c == 0) {
            do {
                ++p;
                count += 8;
                c = *p;
            } while (c == 0);
        }
        c = ~c;
        *p = (unsigned char)c;
        if ((*(volatile unsigned char *)p & 1) == 0)
            return count;
        do {
            count++;
            *p = (unsigned char)((int)*(volatile unsigned char *)p >> 1);
        } while (*(volatile unsigned char *)p & 1);
        return count;
    }
    return 0x20;
}
