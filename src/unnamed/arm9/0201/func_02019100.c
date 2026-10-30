struct Obj;
typedef void (*VFN)(struct Obj*);
struct Obj { VFN* vt; };
extern struct Obj* data_0209d4a8;
extern unsigned char data_0209d464;
/* The end of the VBlank IRQ (IRQ2.cpp): the scene's GraphCallback3 on
   the dGraph_c::callback_c data_0209d4a8 registers, then clear
   data_0209d464, the flag func_020190b8 raises. */
void func_02019100(void){
  struct Obj* o = data_0209d4a8;
  if (o) o->vt[3](o);
  data_0209d464 = 0;
}
