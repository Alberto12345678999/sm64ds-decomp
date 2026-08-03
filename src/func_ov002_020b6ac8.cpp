//cpp
extern "C" {
extern "C" int _ZN16MeshColliderBase9IsEnabledEv(void*);
extern "C" void _ZN16MeshColliderBase7DisableEv(void*);
extern "C" void _ZN13SharedFilePtr7ReleaseEv(void*);
int func_ov002_020b6ac8(void* c, void* r4) {
    if (_ZN16MeshColliderBase9IsEnabledEv((char*)c+0x124))
        _ZN16MeshColliderBase7DisableEv((char*)c+0x124);
    _ZN13SharedFilePtr7ReleaseEv(*(void**)r4);
    _ZN13SharedFilePtr7ReleaseEv(*(void**)((char*)r4+4));
    return 1;
}
}
