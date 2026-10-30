/* out = a - b for a pair of 16-bit (x, y) points: the touch point less a
   menu item's position in Mg_UpdateMenu (d_s_mg_base.cpp), and a stroke's
   end less its start in unit020cd744.cpp. The 2D twin of Vec3_Sub. */
void func_0203b958(short *o, short *a, short *b) {
    int ax = a[0], bx = b[0], ay = a[1], by = b[1];
    o[0] = ax - bx;
    o[1] = ay - by;
}
