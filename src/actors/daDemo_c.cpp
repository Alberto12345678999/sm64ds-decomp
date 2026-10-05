//cpp
/* daDemo_c -- the cutscene-only actor family (_ZTV8daDemo_c).
 * One class services every scripted-scene prop: param1 selects the object
 * (0x12..0x2d plus the 0x2e/0x2f slots dispatched out to other TUs).
 * Animated variants own a ModelAnim at mModelAnim, static variants a Model
 * at mModel.
 *
 * Functions run in ROM order under `#pragma defer_codegen off`; do not
 * reorder. The destructor pair stays in its own shards at 0x020f1f70 --
 * it is the class's key function, so this TU emits no vtable or RTTI.
 * The five lifecycle overrides tile 0x020f8028..0x020f8808 contiguously;
 * the param-dispatch helpers in the func_ov002_020f6* run above are left
 * in their own files for a later pass.
 *
 * Leftover: InitResources still builds the derived cutscene render objects
 * by hand -- _Znwj + member-init veneer + _ZN5ModelC2Ev / _ZN9ModelAnimC2Ev
 * + the two derived vptr stores -- because the derived class they make is
 * unnamed and its member-0x64 subobject is not on any header yet. Render's
 * param1 == 0x19 path copies a ROM matrix constant through a scratch
 * record shape. Both reproduce the cartridge; neither is the original
 * source shape.
 */

#pragma defer_codegen off

#include "types.h"
#include "common.h"
#include "decl_common.h"
#include "decl_Model.h"
#include "decl_ModelAnim.h"
#include "daDemo_c.h"
#include "Model.h"
#include "ModelAnim.h"
#include "dBgCh_Gnd.h"

extern "C" {
void *_Znwj(unsigned int sz);
int func_ov002_020f63a0(void *thiz);
int func_ov002_020f23d0(void *c);
void func_ov002_020f65b8(void *o);
extern unsigned char data_0209f2d8;
extern char data_ov002_0211094c;
extern char data_ov002_0210bcc4;
extern char data_ov002_0210bce8;
extern char data_ov002_0210bae4;
extern char data_ov002_0210bcf0;
extern char data_ov002_0210b600;
extern char data_ov002_0210b604;
extern char data_ov002_0210b608;
extern char data_ov002_0210b60c;
extern char data_ov002_0210b610;
extern char data_ov002_0210bd24;
extern char data_ov002_02110b50;
extern char data_ov002_02110b70;
extern char data_ov002_02110b78;
extern char data_ov002_02110b98;
extern char data_ov002_02110c18;
extern void* data_ov085_0213074c;
extern Matrix4x3 data_020a0e68;
extern void Vec3_Asr(struct Vec3 *d, struct Vec3 *s, int sh);
extern void Matrix4x3_FromTranslation(Matrix4x3 *m, s32 x, s32 y, s32 z);
extern void Matrix4x3_ApplyInPlaceToRotationZXYExt(void *m, s32 x, s32 y, s32 z);
extern void Matrix4x3_ApplyInPlaceToRotationXYZExt(void *m, s32 x, s32 y, s32 z);
}

struct Vec3 { s32 x, y, z; };

// @symbol _ZN8daDemo_c16CleanupResourcesEv
int daDemo_c::CleanupResources()
{
    int r1 = param1;
    if (r1 == 0x2e) return func_ov002_020f63a0(this);
    if (r1 == 0x2f) return func_ov002_020f23d0(this);
    if (mModel) delete mModel;
    if (mModelAnim) delete mModelAnim;
    return 1;
}

// @symbol _ZN8daDemo_c16OnPendingDestroyEv
void daDemo_c::OnPendingDestroy()
{
}

// @symbol _ZN8daDemo_c6RenderEv
int daDemo_c::Render()
{
    if (param1 == 0x19) {
        struct { char* p; char* cur; Matrix4x3* src; } s;
        extern Matrix4x3 data_0209b41c;
        s.src = &data_0209b41c;
        s.p = (char*)mModel + 0x1c;
        s.cur = s.p;
        *(Matrix4x3*)s.cur = *s.src;
        int* tbl = data_ov002_0210bb7c;
        int i = 0;
        int zero = 0;
        do {
            *(int*)(s.p + 0x24) = tbl[0];
            *(int*)(s.p + 0x28) = tbl[1];
            *(int*)(s.p + 0x2c) = tbl[2];
            mModel->Render((const Vector3*)zero);
            tbl += 3;
            i++;
        } while ((unsigned)i < 3u);
        return 1;
    }
    unsigned char op = mOpacity;
    if (op == 0) return 1;
    if (mModel != 0) {
        mModel->ApplyOpacity(op, 0);
        mModel->Render((const Vector3*)&mScaleX);
    } else if (mModelAnim != 0) {
        func_ov002_020f65b8(mModelAnim);
        mModelAnim->ApplyOpacity(mOpacity, 0);
        mModelAnim->Render((const Vector3*)&mScaleX);
    }
    return 1;
}

// @symbol _ZN8daDemo_c8BehaviorEv
int daDemo_c::Behavior()
{
    Vector3 v;
    Vec3 asr;
    int new_var2;
    u32 t;
    t = param1;
    if (t == 0x2e) {
        return func_ov002_020f63d4(this);
    }
    if (t == 0x2f) {
        return func_ov002_020f23f0(this);
    }
    if (t >= 0x1a && t <= 0x2d) {
        UpdatePosWithOnlySpeed(0);
    } else {
        UpdatePos(0);
    }
    {
        u8 *g = (u8*)mModelAnim;
        if (g != 0 && g[0x83] != 0) {
            s32 xx = mPosX;
            s32 yy = mPosY;
            s32 zz = mPosZ;
            new_var2 = yy + 0x96000;
            v.x = xx;
            v.y = new_var2;
            v.z = zz;
            dBgCh_Gnd ground;
            ground.SetObjAndPos(v, 0);
            if (ground.DetectClsn() != 0) {
                s32 h = ground.clsnY;
                if (mPosY < h) {
                    mPosY = h;
                    unk_103 |= 1;
                }
            }
        }
    }
    Vec3_Asr(&asr, (Vec3*)&mPosX, 3);
    Matrix4x3_FromTranslation(&data_020a0e68, asr.x, asr.y, asr.z);
    t = param1;
    if (t >= 0x1a && t <= 0x2d) {
        Matrix4x3_ApplyInPlaceToRotationZXYExt(&data_020a0e68, mAngleX, mAngleY, mAngleZ);
    } else {
        Matrix4x3_ApplyInPlaceToRotationXYZExt(&data_020a0e68, mAngleX, mAngleY, mAngleZ);
    }
    if (mModel != 0) {
        mModel->mat4x3 = data_020a0e68;
    }
    if (mModelAnim != 0) {
        mModelAnim->mat4x3 = data_020a0e68;
        func_ov002_020f64ac(mModelAnim, &data_ov002_0210bc88);
        func_ov002_020f65ec(mModelAnim);
    }
    return 1;
}

// @symbol _ZN8daDemo_c13InitResourcesEv
int daDemo_c::InitResources()
{
    void *p;
    int t;

    if (param1 == 0x12) {
        p = _Znwj(0x84);
        if (p) {
            func_ov002_020f6a50((char *)p + 0x64);
            _ZN9ModelAnimC2Ev(p);
            *(void **)p = &data_ov002_0210bcc4;
            *(void **)((char *)p + 0x50) = &data_ov002_0210bce8;
        }
        mModelAnim = (ModelAnim*)p;
        if (mModelAnim == 0) return 0;
        if (func_ov002_020f6618(mModelAnim, &data_ov085_0213074c, 1, &data_ov002_0210b60c, 1, 1, &data_ov002_0210b608, -1) == 0) return 0;
    } else if (param1 == 0x13) {
        p = _Znwj(0x84);
        if (p) {
            func_ov002_020f6a50((char *)p + 0x64);
            _ZN9ModelAnimC2Ev(p);
            *(void **)p = &data_ov002_0210bcc4;
            *(void **)((char *)p + 0x50) = &data_ov002_0210bce8;
        }
        mModelAnim = (ModelAnim*)p;
        if (mModelAnim == 0) return 0;
        t = (*(volatile unsigned char *)&data_0209f2d8 == 2);
        if (t == 0) {
            if (func_ov002_020f6618(mModelAnim, &data_ov002_02110b98, 1, &data_ov002_0210b610, 1, 1, &data_ov002_0210b600, 0x16) == 0) return 0;
        } else {
            if (func_ov002_020f6618(mModelAnim, &data_ov002_02110c18, 0xD, &data_ov002_0210bcf0, 1, 0xD, &data_ov002_0210bd24, 0x16) == 0) return 0;
        }
    } else if (param1 >= 0x14 && param1 <= 0x16) {
        p = _Znwj(0x60);
        if (p) {
            func_ov002_020f6a50((char *)p + 0x50);
            _ZN5ModelC2Ev(p);
            *(void **)p = &data_ov002_0210bae4;
        }
        mModel = (Model*)p;
        if (mModel == 0) return 0;
        if (func_ov002_020f6960(mModel, &data_ov002_02110b70, -1) == 0) return 0;
    } else if (param1 == 0x17) {
        p = _Znwj(0x60);
        if (p) {
            func_ov002_020f6a50((char *)p + 0x50);
            _ZN5ModelC2Ev(p);
            *(void **)p = &data_ov002_0210bae4;
        }
        mModel = (Model*)p;
        if (mModel == 0) return 0;
        if (func_ov002_020f6960(mModel, &data_ov002_02110b50, 0x19) == 0) return 0;
    } else if (param1 == 0x18) {
        p = _Znwj(0x60);
        if (p) {
            func_ov002_020f6a50((char *)p + 0x50);
            _ZN5ModelC2Ev(p);
            *(void **)p = &data_ov002_0210bae4;
        }
        mModel = (Model*)p;
        if (mModel == 0) return 0;
        if (func_ov002_020f6960(mModel, &data_ov002_0211094c, -1) == 0) return 0;
    } else if (param1 == 0x19) {
        p = _Znwj(0x60);
        if (p) {
            func_ov002_020f6a50((char *)p + 0x50);
            _ZN5ModelC2Ev(p);
            *(void **)p = &data_ov002_0210bae4;
        }
        mModel = (Model*)p;
        if (mModel == 0) return 0;
        if (func_ov002_020f6960(mModel, &data_ov002_02110b78, 0x13) == 0) return 0;
    } else if (param1 >= 0x1A && param1 <= 0x2D) {
        p = _Znwj(0x84);
        if (p) {
            func_ov002_020f6a50((char *)p + 0x64);
            _ZN9ModelAnimC2Ev(p);
            *(void **)p = &data_ov002_0210bcc4;
            *(void **)((char *)p + 0x50) = &data_ov002_0210bce8;
        }
        mModelAnim = (ModelAnim*)p;
        if (mModelAnim == 0) return 0;
        if (func_ov002_020f6618(mModelAnim, data_ov009_02113c20, 1, &data_ov002_0210b604, 0, 0, 0, -1) == 0) return 0;
    }
    mScaleX = 0x1000;
    mScaleY = 0x1000;
    mScaleZ = 0x1000;
    return 1;
}
