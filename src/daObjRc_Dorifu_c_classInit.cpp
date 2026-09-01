//cpp
// @symbol daObjRc_Dorifu_c_classInit
extern "C" {
extern void* _ZN7fBase_cnwEj(unsigned);
extern void _ZN10dBgActor_cC2Ev(void*);
extern void func_020733a8(void*,int,int,void*,void*);
extern int _ZTV13daObjDorifu_c[];
extern int _ZTV16daObjRc_Dorifu_c[];
extern void _ZN5ModelD1Ev(void*);
extern void _ZN5ModelC1Ev(void*);
extern void _ZN10dBgW_KcMbgD1Ev(void*);
extern void _ZN10dBgW_KcMbgC1Ev(void*);
/* Reconstructed source-style name: SM64DS proves daObjRc_Dorifu_c through
 * RTTI, allocation size, vtable identity, and the RC_DORIFU registry profile;
 * later EAD lineage supplies classInit. Exact original spelling is not
 * preserved. The project's TrickyTriangles implementation alias remains
 * unchanged. Historical alias: TrickyTriangles_Spawn. */
void* daObjRc_Dorifu_c_classInit(void){
  char* c = (char*)_ZN7fBase_cnwEj(0xdcc);
  if(c){
    _ZN10dBgActor_cC2Ev(c);
    *(int*)c = (int)_ZTV13daObjDorifu_c;
    func_020733a8(c+0x320, 5, 0x50, (void*)_ZN5ModelC1Ev, (void*)_ZN5ModelD1Ev);
    func_020733a8(c+0x4b0, 5, 0x1c8, (void*)_ZN10dBgW_KcMbgC1Ev, (void*)_ZN10dBgW_KcMbgD1Ev);
    *(int*)c = (int)_ZTV16daObjRc_Dorifu_c;
  }
  return c;
}
}
