extern unsigned char data_02099e18;
/* How many players are present: func_0203ea5c counts the records whose
   flag 0x8000 is set; it is 1 for local play (func_0203df40) and while
   func_0203db64 starts the link. */
int func_0203daac(void) {
    return data_02099e18;
}
