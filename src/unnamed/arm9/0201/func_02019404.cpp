extern void* data_0209d4a8;
/* The scene's GraphCallback1 (data_0209d4a8): the main loop runs it after
   the scene step (func_02044120), before the frame wait. */
void func_02019404(void){
  void** o = (void**)data_0209d4a8;
  if(!o) return;
  void** vt = (void**)o[0];
  ((void(*)(void*))vt[1])(o);
}
