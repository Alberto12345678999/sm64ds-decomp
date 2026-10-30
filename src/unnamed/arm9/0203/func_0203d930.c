extern unsigned short data_020a1040[];

/* Drop the load request, flag 0x4000 of this console's input record
   (func_0203d918), once the course resources are in (dScEntry_c, dScMB_c). */
void func_0203d930(void) {
    data_020a1040[6] &= 0xbfff;
}
