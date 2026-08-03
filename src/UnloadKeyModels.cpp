//cpp
extern "C" {
extern "C" int _ZN13SharedFilePtr7ReleaseEv(void*);
extern void* data_ov089_02132894[];
extern void* data_ov089_021328b4[];
void UnloadKeyModels(int i){
  if(i>=8) return;
  _ZN13SharedFilePtr7ReleaseEv(data_ov089_02132894[i]);
  if(data_ov089_021328b4[i]==0) return;
  _ZN13SharedFilePtr7ReleaseEv(data_ov089_021328b4[i]);
}
}
