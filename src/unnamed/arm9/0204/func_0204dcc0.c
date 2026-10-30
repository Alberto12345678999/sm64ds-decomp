/* The default projection for a tracked particle (func_0204dab4): the
   screen x and y are the position's whole parts, y negated, and the
   weight is 0xfff. */
void func_0204dcc0(int *src, short *o1, short *o2, int *o3) {
    *o1 = (short)(src[0] >> 12);
    *o2 = (short)((-src[1]) >> 12);
    *o3 = 0xfff;
}
