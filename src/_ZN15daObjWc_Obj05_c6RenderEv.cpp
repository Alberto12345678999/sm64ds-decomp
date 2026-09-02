//cpp
// @symbol _ZN15daObjWc_Obj05_c6RenderEv
#include "daObjWc_Obj05_c.h"
// recovered name: daObjWc_Obj05_c_Render
/* recovered: renamed to Class_Method */
/* daObjWc_Obj05_c::Render - recovered from vtable slot identity */
struct Base { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void m(int); };
struct Derived { char pad[0xd4]; Base base; };
s32 daObjWc_Obj05_c::Render() {
    Derived * d = (Derived *)this; Base *b = &d->base; b->m(0); return 1; }
