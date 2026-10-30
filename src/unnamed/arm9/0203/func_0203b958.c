/* out = a - b for a pair of 16-bit (x, y) points: the touch point less a
   menu item's position in Mg_UpdateMenu (d_s_mg_base.cpp), and a stroke's
   end less its start in unit020cd744.cpp. The 2D twin of Vec3_Sub. */
void func_0203b958(short *o, short *a, short *b) {
    int a0 = a[0], b0 = b[0], a1 = a[1], b1 = b[1];
    o[0] = a0 - b0;
    o[1] = a1 - b1;
}
