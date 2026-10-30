extern unsigned short data_020a0f1c;
extern unsigned char data_020a1040[];
/* Clear the link error bits 0x9f of data_020a0f1c and byte 0x22 of the
   local input record data_020a1040. func_02030aa4 calls it when a session
   starts, and dMeter_c when it sets up. */
void func_0203da4c(void){
  unsigned int v = data_020a0f1c & 0xff60;
  *(unsigned char*)(data_020a1040+0x22) = 0;
  data_020a0f1c = v;
  *(unsigned char*)(data_020a1040+0x22) = 0;
}
