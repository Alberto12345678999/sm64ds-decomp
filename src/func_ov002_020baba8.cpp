//cpp
extern "C" {
extern "C" int _ZN16MeshColliderBase9IsEnabledEv(void*);
extern "C" void _ZN16MeshColliderBase7DisableEv(void*);
extern "C" void _ZN13SharedFilePtr7ReleaseEv(void*);
int func_ov002_020baba8(char* c, void** p){
  if(_ZN16MeshColliderBase9IsEnabledEv(c+0x124))
    _ZN16MeshColliderBase7DisableEv(c+0x124);
  _ZN13SharedFilePtr7ReleaseEv(p[0]);
  _ZN13SharedFilePtr7ReleaseEv(p[1]);
  return 1;
}
}
